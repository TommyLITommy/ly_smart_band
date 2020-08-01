#include <stdint.h>
#include <math.h>
#include "heart_rate_data_handle.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "acceleration_data_handle_temp.h"


uint32_t  smoothDataHeartRate=0;
int32_t  dif = 1;
int32_t  lastDif= 1;
int32_t   pointBuf[10] = { 0 };
uint32_t  pointBufLen = 0;
uint32_t  th0 = 100;
uint32_t  lsTh0 = 100;
int32_t  difMax = 0;
int32_t  difMin = 0;
int8_t  flag = 0;

uint8_t  heart0 = 0;
uint8_t  lastHeart = 0;
uint8_t  heart = 0;
uint8_t  averageHeart = 0;
uint32_t  heartSum = 0;
uint32_t  len = 0;
uint8_t ctinuHeart = 0;
uint8_t jCtinuHeart = 0 ;
uint8_t nCtinuHeart = 0 ;
uint8_t flagHeart = 0;
uint8_t changeLen = 0;
uint32_t ctinuDifCount = 0;
uint32_t difIndex = 0;
uint32_t number = 0;

uint16_t bufHeart[20] = {0};
uint16_t bufHeartAverage = 0;
uint8_t lastBufHeartAverage = 0;
uint8_t bufHeartLen = 0;
uint32_t bufHeartSum = 0;
uint16_t RestingHeart = 0;//静息心率
uint8_t RestingHeartFlag = 0;

uint32_t  smoothWindows[2] = { 0 };
uint32_t  smoothWindowsNext[2] = { 0 };
uint32_t  smoothWindowsNextTwo[2] = { 0 };
uint32_t  smoothWindowsNextThree[2] = { 0 };
uint32_t  smoothWindowsNextFour[2] = { 0 };
uint32_t  difWindows[5] = { 0 };

/*********信号质量评估************/
uint8_t noPulseWave = 0;
uint8_t ctinuEqualData = 0;
uint16_t lastData = 0;
uint16_t curData = 0;
uint8_t ctinuEqualHeart = 0;
uint8_t signalQuality = 0;


/*****************动态心率*********************/
uint16_t mov_heart_buf[18] = {0};//存放动态心率数组
uint8_t mov_bufHeartLen  = 0;//找到脉搏波个数
uint16_t mov_sum_buf_heart = 0;//数组心率和
uint16_t mov_max_data = 0;//最大有效心率值
uint16_t Stepfrequency = 0;//步频
uint16_t Resting_heart_ctinu = 0;
uint8_t movflag = 0;
/***************动态心率************************/

/**********判断趋势增减**********/
uint8_t Increase = 0;//增加
uint8_t Decreases = 0;//减少


static uint32_t Algo_count = 0;
static uint32_t 	Algo_Num = 0;

/****************Blood pressure Start********************/ 
uint32_t PPG_Ps,PPG_Pd;//用于存放PPG数据中的PS,PD；
extern uint8_t SigwaveLength=0;//分离出单波的个数；
uint32_t PPG_max=0,PPG_min=0;//波形的最值；
uint32_t PPG_PS_Sum,PPG_PD_Sum;//一屏共6个波形后脉搏波的PS、PD的和；
uint32_t PPG_PS_average,PPG_PD_average;//PS、PD的均值。
uint8_t  PS,PD;//收缩压、舒张压；

static uint8_t user_age;


static uint8_t user_height;
static uint8_t user_weight;
static uint8_t user_gender;
/****************Blood pressure End********************/

/********************************************************************
 *
 * Function Name:   whether_saturation_is_saturated
 * Input:           source_data - 原始数据;
 *                  
 * Output:          变量值no_pulse_wave为2表示输入信号饱和
 * Description:     判断信号是否饱和.
 *
 **********************************************************************/

void whether_saturation_is_saturated(uint16_t source_data)
{
	  lastData = curData;
    curData = source_data;
    if (curData==lastData)
        ctinuEqualData = ctinuEqualData + 1;
    else
        ctinuEqualData = 0;
   
    if (ctinuEqualData == 5)
		{
        noPulseWave = 2;
			  //NRF_LOG_RAW_INFO("%d\r\n", 2);		
			  ctinuEqualData = 0;
		} 
}

/********************************************************************
 *
 * Function Name:   smoothingFilter
 * Input:           index - 数据的索引
                    windows - 平滑滤波数组
                    source_data - 滤波前的数据
 *                  
 * Output:          滤波后的数据
 * Description:     对数据进行滤波处理
 *
 **********************************************************************/

void smoothingFilter(uint32_t index, uint32_t *windows, uint32_t source_data)
{
	int8_t k = 0;
	uint32_t sum = 0;
	windows[0] = windows[1];
	windows[1] = source_data;
	for (k = 0; k < 2; k++)
	{
		sum = sum + windows[k];
	}
	if (index >= 2)
	{
		smoothDataHeartRate = sum / 2;
	}
	else
	{
		smoothDataHeartRate = source_data;
	}	
}

/********************************************************************
 *
 * Function Name:   diff
 * Input:           index - 数据的索引
                    windows - 用于差分运算的数组
                    source_data - 滤波前的数据
 *                  
 * Output:          输出差分后的数据，并检测脉搏波的波谷值点的位置，存于point_buf中
 * Description:     对数据进行差分处理，并找出脉搏波的波谷值点的位置
 *
 **********************************************************************/

void diff(uint32_t index, uint32_t *windows, uint32_t source_data)
{
	int8_t j = 0;
	lastDif = dif;
	for (j = 0; j < 4; j++)
	{
		windows[j] = windows[j + 1];
	}
	windows[4] = source_data;

	if (index < 5)
	{
		dif = windows[4] - windows[3];
	}
	else
	{
		dif = 2 * windows[4] + windows[3] - windows[1] - 2 * windows[0];
	}

		if (dif-lastDif>=0)
		{
			 if (ctinuDifCount == 0)
			 {
            difMin = lastDif;
            difIndex = index-2;
			 }      
        ctinuDifCount = ctinuDifCount + 1;
        if (lastDif<=0&&dif>=0)
            difIndex = index-2;     
			PPG_Pd=smoothDataHeartRate;//娉㈣胺鐐逛綅缃紱
		}   
    else
		{

		if(dif<0 && lastDif>0)
		{
			PPG_Ps=smoothDataHeartRate;	//鎵炬尝宄扮偣鐨勪綅缃紱
		}  
		
        if (ctinuDifCount >=4)
					
				{
            lsTh0 = th0;           
            if (lsTh0<100) 
                lsTh0 = 100;            
            difMax = lastDif;
            th0 = difMax - difMin;
            if (th0>=0.4*lsTh0)							
						{
							if (number > 0)
							{
								if (difIndex - pointBuf[number]>5)
								{
							    number = number + 1;
                  pointBuf[number] = difIndex; 	
								}
							}
							else
							{
								number = number + 1;
                pointBuf[number] = difIndex; 
							}
						}                            
				}
        ctinuDifCount = 0;
		}
}

/********************************************************************
 *
 * Function Name:   detect
 * Input:           source_data - 原始数据
                    buf_len - 检测到脉搏波波谷的个数
                    p_buf - 存储每一秒内脉搏波
                    n - 第几个一秒

 * Output:          输出每一秒后的心率值
 * Description:     对每秒检测到的脉搏波波谷位置进行计算，得出每一秒钟的心率值，
                    刚进行心率检测时，进行佩戴检测，手环从手腕取下时，检测是否佩戴。
 *
 **********************************************************************/

void detect( uint16_t source_data,uint32_t buf_len, int32_t *p_buf, uint32_t n)
{	
	int8_t j = 1;
	int8_t i = 0;
	uint32_t heart_buf_sum = 0;
	static uint8_t heart_temp = 0;
	int8_t flag_len = 0;
	uint8_t temp_max = 40;
	uint8_t tem_min = 200;
	if (n == 6)
	{		
				j = 1;
				while (j < buf_len)
				{			
						heart_temp = 25 * 60 / (p_buf[j + 1] - p_buf[j]);
						if (heart_temp<120 && heart_temp>40)
						{
							heart_buf_sum = heart_buf_sum + heart_temp;
							flag_len = flag_len + 1;
							if (heart_temp>temp_max)
								temp_max = heart_temp;
							if (tem_min>heart_temp)
								tem_min = heart_temp;
						}
						j = j + 1;						
				}
				if (flag_len >2)
				{
					bufHeartAverage = (heart_buf_sum - tem_min - temp_max) / (flag_len - 2);
					RestingHeart = bufHeartAverage; 
          //NRF_LOG_RAW_INFO("%d,RestingHeart = %d,bufHeartAverage = %d\r\n",1,RestingHeart, bufHeartAverage);						
				}
				else	
				{            
						bufHeartAverage = 0;
				}
	  
		pointBuf[1] = pointBuf[buf_len];      
		buf_len = 0;

		if (bufHeartAverage == 0 && (source_data>61500 || source_data==0))
		{
			noPulseWave = 3;
			//NRF_LOG_RAW_INFO("%d\r\n", noPulseWave);
		}
		if (flag_len <= 1 &&  bufHeartAverage == 0 && source_data<=61500 && source_data>0)
		{
			noPulseWave = 1;
			//Algo_Num = 0;
		}
		if(bufHeartAverage == 0)
		{
		  Algo_Num = 0;
			//NRF_LOG_RAW_INFO("%d,%5d\r\n", 55,Algo_Num);
		}
	}
	if (n>6)
	{
		  //信号比较差的情况下的显示no_pulse_wave = 1；
		//NRF_LOG_RAW_INFO("ctinuEqualHeart = %d, source_data = %d\r\n", ctinuEqualHeart, source_data);	
			if ((heart - averageHeart)>25 && (heart-averageHeart)<-25 && (source_data>62500 || source_data==0))
			{
				ctinuEqualHeart++;	
				//NRF_LOG_RAW_INFO("ctinuEqualHeart = %d, source_data = %d\r\n", ctinuEqualHeart, source_data);		
				if (ctinuEqualHeart == 10)//&&(source_data>61000||source_data==0)
				{				
					noPulseWave = 3;				
					ctinuEqualHeart = 0;					
				}
			}
			else
			{			
				ctinuEqualHeart = 0;
			}

      if ((heart - averageHeart)>25 && (heart-averageHeart)<-25 && source_data<=61500 )
			{
					 ctinuHeart = ctinuHeart + 1;
			}
			else
			{
					 ctinuHeart = 0;
			}
		 if(ctinuHeart == 6 )
		 {
			   //bufHeartAverage = averageHeart;
				 noPulseWave = 1;				   
				 //ctinuHeart = 0;			  
		 }
								
		flagHeart = 0;		
		while (j < buf_len)
		{							
			lastHeart = bufHeartAverage;			
			heart = 25 * 60 / (p_buf[j+1] - p_buf[j]);			
			j = j + 1;      						
			if (heart<40 || heart>200)
			{
			    heart = lastHeart;
			}
			else
			{				
          if (lastHeart > 0 )	
					{						
					    len = len + 1;
						  heartSum = heartSum + lastHeart;	
					    averageHeart = heartSum / (len);
					}							
								
			/************动态心率计算***************/								
			if( ctinu_wave >= 6 || (ctinu_wave > 0  && zcount  == 0)  )
			{
				//NRF_LOG_RAW_INFO("%d,ctinu_wave = %d,heart = %d\r\n",0,ctinu_wave, heart);	
          NRF_LOG_RAW_INFO("%d,ctinu_wave = %d,xcount = %d,ycount = %d,zcount = %d,heart = %d\r\n",0,ctinu_wave,xcount,ycount,zcount,heart);				
				  movflag = 0;				 
				  RestingHeartFlag = 0;
				  if( bufHeartLen > 0)
				  {
						
             bufHeartLen = 0; 							
             for (i = 0; i < 18; i++)
					   {
							   mov_heart_buf[i] = 0;
					   }						
						 if(lastHeart>0)
						 {
								 mov_heart_buf[17] = lastHeart;
								 mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
						 if(bufHeart[18]>0)
						 {
								 mov_heart_buf[16] = bufHeart[18];
								 mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
						 if(bufHeart[17]>0)
						 {
								 mov_heart_buf[15] = bufHeart[17];
								 mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
						 if(bufHeart[16]>0)
						 {
								 mov_heart_buf[14] = bufHeart[16];
								 mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
						 if(bufHeart[15]>0)
						 {
								 mov_heart_buf[13] = bufHeart[15];
								 mov_bufHeartLen = mov_bufHeartLen + 1;
						 }						 
						 if(bufHeart[14]>0)
						 {
								 mov_heart_buf[12] = bufHeart[14];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }						 
						 if(bufHeart[13]>0)
						 {
								 mov_heart_buf[11] = bufHeart[13];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }	
						 if(bufHeart[12]>0)
						 {
								 mov_heart_buf[10] = bufHeart[12];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }	
						 if(bufHeart[11]>0)
						 {
								 mov_heart_buf[9] = bufHeart[11];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[10]>0)
						 {
								 mov_heart_buf[8] = bufHeart[10];
								 //mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[9]>0)
						 {
								 mov_heart_buf[7] = bufHeart[9];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[8]>0)
						 {
								 mov_heart_buf[6] = bufHeart[8];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[7]>0)
						 {
								 mov_heart_buf[5] = bufHeart[7];
								 //mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[6]>0)
						 {
								 mov_heart_buf[4] = bufHeart[6];
								 //mov_bufHeartLen = mov_bufHeartLen + 1;
						 }	
             if(bufHeart[5]>0)
						 {
								 mov_heart_buf[3] = bufHeart[5];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[4]>0)
						 {
								 mov_heart_buf[2] = bufHeart[4];
								// mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[3]>0)
						 {
								 mov_heart_buf[1] = bufHeart[3];
								 //mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
             if(bufHeart[2]>0)
						 {
								 mov_heart_buf[0] = bufHeart[2];
								 //mov_bufHeartLen = mov_bufHeartLen + 1;
						 }
           //NRF_LOG_RAW_INFO("%d,mov_bufHeartLen = %d,bufHeartAverage = %d\r\n",1,mov_bufHeartLen, bufHeartAverage);						 
				  }			
				
				 if ((bufHeartAverage-heart<=30)&&(bufHeartAverage-heart>=-30) && (heart >= RestingHeart && RestingHeart > 0) && mov_bufHeartLen > 2 )
				 {
					 if(heart > mov_max_data )
					 {
							mov_max_data = heart; 
					 }										 
					if(bufHeartAverage <= heart && bufHeartAverage <= mov_max_data)
					{
							bufHeartAverage =heart  ;
					}
					
					if (bufHeartAverage > heart && bufHeartAverage >= RestingHeart && mov_bufHeartLen > 4)
					{
							bufHeartAverage = bufHeartAverage + 0.5*(heart - bufHeartAverage);
					}		
										
					for (i = 0; i < 17; i++)
					{
							mov_heart_buf[i] = mov_heart_buf[i + 1];
					}
					  mov_bufHeartLen = mov_bufHeartLen + 1;
					  mov_heart_buf[17] = bufHeartAverage;
												 
						if (mov_bufHeartLen > 18)
						{					
							 mov_bufHeartLen = 18;
						}	
           mov_sum_buf_heart = 0;						
					 for (i = 0;i < mov_bufHeartLen; i++)
					 {						 
							mov_sum_buf_heart = mov_sum_buf_heart + mov_heart_buf[17-i];
					 }			          					 
					 
					if (mov_bufHeartLen < 18 )
					{			
						 bufHeartAverage = mov_sum_buf_heart / mov_bufHeartLen;							
					}
					else 
					{			           					
						 bufHeartAverage = mov_sum_buf_heart / 18; 								
					}	
         // NRF_LOG_RAW_INFO("%d,mov_bufHeartLen = %d,bufHeartAverage = %d\r\n",2,mov_bufHeartLen, bufHeartAverage);						
			 }		 
			 else
			 {
          				 
				 	mov_bufHeartLen = mov_bufHeartLen + 1;
	        for (i = 0; i < 17; i++)
					{
							mov_heart_buf[i] = mov_heart_buf[i + 1];
					}										 
				  if (bufHeartAverage >= heart)
					{						
						 mov_heart_buf[17] = bufHeartAverage - 3;	
             //NRF_LOG_RAW_INFO("%d,mov_bufHeartLen = %d,bufHeartAverage = %d\r\n",3,mov_bufHeartLen,bufHeartAverage);							
					}
					else
					{						
						 mov_heart_buf[17] = bufHeartAverage + 6;	
						//NRF_LOG_RAW_INFO("%d,mov_bufHeartLen = %d,bufHeartAverage = %d\r\n",4,mov_bufHeartLen,bufHeartAverage);
					}
					 mov_sum_buf_heart = 0;						
					 for (i = 0;i < mov_bufHeartLen; i++)
					 {						 
							mov_sum_buf_heart = mov_sum_buf_heart + mov_heart_buf[17-i];
					 }			          					 
					// NRF_LOG_RAW_INFO("%d,mov_bufHeartLen = %d,mov_sum_buf_heart = %d\r\n",33,mov_bufHeartLen,mov_sum_buf_heart);	
					if (mov_bufHeartLen < 18 )
					{			
						 bufHeartAverage = mov_sum_buf_heart / mov_bufHeartLen;							
					}
					else 
					{		
             mov_bufHeartLen = 18;					
						 bufHeartAverage = mov_sum_buf_heart / 18; 								
					}	
          					
			} 
			 //NRF_LOG_RAW_INFO("%d,mov_bufHeartLen = %d,bufHeartAverage = %d\r\n",22,mov_bufHeartLen, bufHeartAverage);	
     movflag = 1;		 
   }		
	 else
	    { 
				NRF_LOG_RAW_INFO("%d,ctinu_wave = %d,xcount = %d,ycount = %d,zcount = %d, heart = %d\r\n",5,ctinu_wave,xcount,ycount,zcount, heart);					
					mov_max_data = 0;	
          if( mov_bufHeartLen > 0)
					{
						mov_bufHeartLen = 0;  
						for (i = 0; i < 19; i++)
						{
								bufHeart[i] =0;
						}
						 if(lastHeart > 0)
						 {
							 bufHeart[19]= lastHeart;
							 bufHeartLen = bufHeartLen + 1;
						 }
						 if(mov_heart_buf[16] > 0)
						 {
							 bufHeart[18] = mov_heart_buf[16];
							 bufHeartLen = bufHeartLen + 1;
						 }
						 if(mov_heart_buf[15] > 0)
						 {
							 bufHeart[17] = mov_heart_buf[15];
							 bufHeartLen = bufHeartLen + 1;
						 }
						 if(mov_heart_buf[14] > 0)
						 {
							 bufHeart[16] = mov_heart_buf[14];
							 bufHeartLen = bufHeartLen + 1;
						 }
						 if(mov_heart_buf[13] > 0) 
						 {
							 bufHeart[15] = mov_heart_buf[13];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[12] > 0) 
						 {
							 bufHeart[14] = mov_heart_buf[12];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[11] > 0) 
						 {
							 bufHeart[13] = mov_heart_buf[11];
							 bufHeartLen = bufHeartLen + 1;
						 }
             if(mov_heart_buf[10] > 0) 
						 {
							 bufHeart[12] = mov_heart_buf[10];
							 bufHeartLen = bufHeartLen + 1;
						 }
             if(mov_heart_buf[9] > 0) 
						 {
							 bufHeart[11] = mov_heart_buf[9];
							 bufHeartLen = bufHeartLen + 1;
						 }
             if(mov_heart_buf[8] > 0) 
						 {
							 bufHeart[10] = mov_heart_buf[8];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[7] > 0) 
						 {
							 bufHeart[9] = mov_heart_buf[7];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[6] > 0) 
						 {
							 bufHeart[8] = mov_heart_buf[6];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[5] > 0) 
						 {
							 bufHeart[7] = mov_heart_buf[5];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[4] > 0) 
						 {
							 bufHeart[6] = mov_heart_buf[4];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[3] > 0) 
						 {
							 bufHeart[5] = mov_heart_buf[3];
							 bufHeartLen = bufHeartLen + 1;
						 }	
             if(mov_heart_buf[2] > 0) 
						 {
							 bufHeart[4] = mov_heart_buf[2];
							 bufHeartLen = bufHeartLen + 1;
						 }
             if(mov_heart_buf[1] > 0) 
						 {
							 bufHeart[3] = mov_heart_buf[1];
							 bufHeartLen = bufHeartLen + 1;
						 }							 
             if(mov_heart_buf[0] > 0) 
						 {
							 bufHeart[2] = mov_heart_buf[0];
							 bufHeartLen = bufHeartLen + 1;
						 }
            // NRF_LOG_RAW_INFO("%d,bufHeartLen = %d,bufHeartAverage = %d\r\n",5,bufHeartLen, bufHeartAverage);						 
					}
					
					if ((averageHeart - heart) <= 25 && (averageHeart - heart) >= -25 )
					{											
						bufHeartLen = bufHeartLen + 1;
						for (i = 0; i < 19; i++)
						{
								bufHeart[i] = bufHeart[i + 1];
						}
						bufHeart[19] = heart;						
					              
						  bufHeartSum = 0;
							for(i = 0; i<bufHeartLen; i++)
							{
								bufHeartSum = bufHeartSum + bufHeart[ 19 - i ];
							}
						
							if(bufHeartLen > 20)	
							{
								bufHeartLen = 20; 
							}	
						
							bufHeartAverage = bufHeartSum/bufHeartLen;						
						//NRF_LOG_RAW_INFO("%d,heart = %d,bufHeartAverage = %d\r\n",6,heart, bufHeartAverage);	
							if((averageHeart-bufHeartAverage)<=3&&(averageHeart-bufHeartAverage)>=-3)
							{
								if (bufHeartAverage-lastHeart<=3 && bufHeartAverage-lastHeart>=1&&Decreases==0)
								{
									bufHeartAverage = lastHeart + 1;
									//NRF_LOG_RAW_INFO("%d,averageHeart = %d,bufHeartAverage = %d,lastHeart = %d\r\n",7,averageHeart, bufHeartAverage, lastHeart);	
								}
								if (bufHeartAverage-lastHeart>=-3&&bufHeartAverage-lastHeart<-1&&Increase==0)
								{
									bufHeartAverage = lastHeart - 1;
									//NRF_LOG_RAW_INFO("%d,averageHeart = %d,bufHeartAverage = %d,lastHeart = %d\r\n",8,averageHeart, bufHeartAverage, lastHeart);
								}
							}
							if(bufHeartAverage-lastHeart==1)
							{
								Increase = Increase + 1;
							}
							else
							{
								Increase = 0;
							}
							
							if(bufHeartAverage-lastHeart==-1)
							{
								Decreases = Decreases + 1;
							}
							else
							{
								Decreases = 0;
							}
							//NRF_LOG_RAW_INFO("%d,averageHeart = %d,bufHeartAverage = %d\r\n",16,averageHeart, bufHeartAverage);	
							if(RestingHeartFlag >= 3)
							{
							    RestingHeart = bufHeartAverage; 
							}
							Resting_heart_ctinu = 0;
						}	
						else
						{
							Resting_heart_ctinu = Resting_heart_ctinu + 1;
							if(Resting_heart_ctinu>=10)
							{
								Resting_heart_ctinu = 0;
								bufHeartAverage = heart;
								for(i = 0; i<bufHeartLen; i++)
							  {
								bufHeart[ 19 - i ] = 0;
								
							  }
							  bufHeart[17] = bufHeartAverage;
								bufHeartLen = 1;
							}		
							//NRF_LOG_RAW_INFO("%d,Resting_heart_ctinu = %d,bufHeartAverage = %d,averageHeart = %d\r\n",9,Resting_heart_ctinu, bufHeartAverage, averageHeart);
              /*if( movflag == 1 )							
							{
									if(heart>=bufHeartAverage)
									{
										bufHeartAverage = bufHeartAverage + 1;
										NRF_LOG_RAW_INFO("%d,bufHeartAverage = %d\r\n",11, bufHeartAverage);	
									}							
									else
									{
										bufHeartAverage = bufHeartAverage - 1;
										NRF_LOG_RAW_INFO("%d,bufHeartAverage = %d\r\n",10, bufHeartAverage);	
									}
							}*/
						}
					           
						RestingHeartFlag = RestingHeartFlag + 1;							
			 }	
		/************动态心率计算***************/						
				/*if (averageHeart == 0 && bufHeartAverage == 0 && heart > 0)
				{
            bufHeartAverage = heart;  
				}				
			  if ((averageHeart-heart>50) && (averageHeart-heart<-50) && (flagHeart == 0) && averageHeart>0 && mov_flag == 0) 
				{ 	
          NRF_LOG_RAW_INFO("%d,bufHeartAverage = %d\r\n",36, bufHeartAverage);						
					if (lastHeart == averageHeart)
					{
						if (lastHeart+50<heart)
						{
						    bufHeartAverage = lastHeart; 
						}						
						else
						{
						    bufHeartAverage = lastHeart;							
						}						
					}                
				  else if ((averageHeart-heart)>50 || (lastHeart-heart)>50)
				 {
					   bufHeartAverage = lastHeart +1 ;
				 }
				 else if ((averageHeart-heart)<-50 || (lastHeart-heart)<-50)
				 {
					   bufHeartAverage = lastHeart;
				 } 	 
				} */    
			}
		}	
    pointBuf[1] = pointBuf[buf_len];      
		buf_len = 0;		
	}
}

/********************************************************************
 *
 * Function Name:   GetHeartRateValue
 *                  
 * return:          心率值
 * Description:     获取心率值
 *
 **********************************************************************/

uint8_t GetHeartRateValue(void)
{
	  return 	bufHeartAverage;	
}

/********************************************************************
 *
 * Function Name:   GetSignalsState
 *                  
 * return:          0 - 能检测到心率值；1 - 信号质量差不能检测到心率值；2 - 信号饱和；3 - 没配戴手环。
 * Description:     返回信号质量分类类型
 *
 **********************************************************************/

uint8_t GetSignalsState(void)
{
	  uint8_t temp = 0;
	  temp = noPulseWave;
	  noPulseWave = 0;
    return 	temp;
}



/*******************************************************
* 功能：计算心率数据
* 参数：心率传感器采集到的数据
* 返回值：1 - 可以调用GetHeartValue函数读取心率值  
*******************************************************/
uint8_t CalHeartRateValue(uint16_t uAdcData)
{
	  // LY_LOG_INFO("CalHeartRateValue.\r\n");
	   // NRF_LOG_RAW_INFO("%d\r\n", uAdcData);	
	    Algo_count++;
	    whether_saturation_is_saturated(uAdcData);	
		  smoothingFilter(Algo_count, smoothWindows, uAdcData);
	    smoothingFilter(Algo_count, smoothWindowsNext, smoothDataHeartRate);
	    smoothingFilter(Algo_count, smoothWindowsNextTwo, smoothDataHeartRate);
	    smoothingFilter(Algo_count, smoothWindowsNextThree, smoothDataHeartRate);
	    smoothingFilter(Algo_count, smoothWindowsNextFour, smoothDataHeartRate);
      diff(Algo_count, difWindows, smoothDataHeartRate); 
    	     	
      if (Algo_count % 25 == 0)
      {           
         Algo_Num = Algo_Num + 1;
         if (Algo_Num >= 6)
         {
             detect(uAdcData,number, pointBuf, Algo_Num);
             number = 1;
					   //Algo_Num = 7;					 
					   return 1;
         }
     } 		
		 return 0;
}

/********************************************************************
 *
 * Function Name:   clear_heart_rate_data_handle_para
 *                  
 * Description:     变量初始化
 *
 **********************************************************************/

void clear_heart_rate_data_handle_para(void)
{
	  int i = 0;
	  bufHeartAverage = 0;//Attention Please
		bufHeartLen = 0;
	  ctinuEqualHeart = 0;
	  Algo_count = 0;
	  Algo_Num = 0;
	  smoothDataHeartRate = 0;
    number = 0;
	  dif = 1;
	  lastDif = 1;
	  pointBufLen = 0;
	  th0 = 100;
	  lsTh0 = 100;
	  difMax = 0;
	  flag = 0;
	  heart0 = 0;
	  lastHeart = 0;
	  heart = 0;
	  averageHeart = 0;
	  heartSum = 0;
	  len = 0;
    noPulseWave = 0;
    ctinuEqualData = 0;
    lastData = 0;
    curData = 0;
		signalQuality = 0;
		RestingHeartFlag = 0;
		Resting_heart_ctinu = 0; 
		movflag = 0;
		for (i=0;i<sizeof(smoothWindows); i++)
		{
				smoothWindows[i] =0;
			  smoothWindowsNext[i] = 0;
			  smoothWindowsNextTwo[i] = 0;
			  smoothWindowsNextThree[i] = 0;
			  smoothWindowsNextFour[i] = 0;
		}
				
		for (i=0;i<sizeof(difWindows); i++)
		{
				difWindows[i] =0;
		}

    for (i=0; i<20; i++)
    {
			bufHeart[i] = 0;		
		}	
    mov_bufHeartLen = 0;	
    Stepfrequency = 0	;
		for(i = 0 ;i < 18; i++)
		{
		    mov_heart_buf[i] = 0;
		}
		mov_max_data = 0;   
}

void Get_userifo_init(void)
{
	user_age =get_user_info_age();
	user_height =get_user_info_height();
	user_weight =get_user_info_weight();
	user_gender =get_user_info_gender();
}

void Blood_pressure_init(void)
{
	Get_userifo_init();
}


/*******************************************************
* 功能：计算血压结果
* 参数：PPG原始数据，Si114x_functions.c-->void Process_Si114x_INT(void)
-->if(CalHeartRateValue(tmpData) &&CalBloodpressureValue(tmpData))
* 返回值：1 - 可以调用GetBloodpressureValue函数读取血压值  
*******************************************************/

uint8_t Get_PPG_Ps_Pd(void)	
{
	uint8_t PI;
	PI=(PPG_Ps-PPG_Pd)*0.01;
	return PI;
	//return PPG_PS_average;
}

uint8_t CalBloodpressureValue(void)
{ 
	uint8_t hr,time;
	uint8_t PI_A;
	Get_userifo_init();
	PI_A=Get_PPG_Ps_Pd();
	hr=GetHeartRateValue();
	time++;
	if(hr!= 0 && PI_A<40)
		{
	
			if(user_gender)//血压区分男女；
			{
				if( user_weight>=60)
					{
						if(hr>80)
						{
							//W>60,H>170,hr>80
							PS=110+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.2+PI_A*0.3;
							PD=70+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.1+PI_A*0.3;
						}
				   else 
					  {
							//W>60,H>170,hr<80
					  	PS=110+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.2-PI_A*0.3;
					  	PD=70+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.1-PI_A*0.3;
					  }
					}
				else 
				{
					if(hr>80)
						{
							PS=100+user_age/20+(user_weight/50)*3-(user_height-170)*0.3+(hr-80)*0.2+PI_A*0.3;
					  	PD=60+user_age/20+(user_weight/50)*3-(user_height-170)*0.3+(hr-80)*0.1+PI_A*0.3;
						}
				   else 
					  { 
					  	PS=100+user_age/20+(user_weight/50)*3-(user_height-170)*0.3-(hr-80)*0.2-PI_A*0.3;
					  	PD=60+user_age/20+(user_weight/50)*3-(user_height-170)*0.3-(hr-80)*0.1-PI_A*0.3;
					  }
				}
			}
				else 
				{
					if( user_weight>=60)
					{
						if(hr>70)
						{
							PS=110+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.2+PI_A*0.3;
							PD=70+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.1+PI_A*0.3;
						}
				   else 
					  {
					  	//W>60,H>170,hr<80
					  	PS=110+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.2-PI_A*0.3;
					  	PD=70+user_age/20+(user_weight/50)*3+(user_height-170)*0.3+(hr-80)*0.1-PI_A*0.3;
					  }
					}
				else 
				{
					if(hr>70)
						{
							PS=90+user_age/20+(user_weight/50)*3-(user_height-170)*0.3+(hr-80)*0.2+PI_A*0.3;
					  	PD=60+user_age/20+(user_weight/50)*3-(user_height-170)*0.3+(hr-80)*0.1+PI_A*0.3;
						}
				   else 
					  { 
					  	PS=90+user_age/20+(user_weight/50)*3-(user_height-170)*0.3-(hr-80)*0.2-PI_A*0.3;
					  	PD=60+user_age/20+(user_weight/50)*3-(user_height-170)*0.3-(hr-80)*0.1-PI_A*0.3;
					  }
				}
				
				}	
		}
	if(PS!=0 && PD!=0)
		return 1;
	else 
		return 0;
}

/*********************************
uint8_t Get_PI_Return(void)
{
	uint8_t PI_A,PI_SUM;
	PI_A=Get_PPG_Ps_Pd();
	for(i=0;i<6;i++)
		{
			PPG_PS_Sum+=PPG_Ps;
			PPG_PD_Sum+=PPG_Pd;
		}
	PPG_PS_average=PPG_PS_Sum/6;
	PPG_PD_average=PPG_PD_Sum/6;
	PI=(PPG_PS_average-PPG_PD_average)*0.01;	
}
**********************************/
	/*******************************************************
* 功能：计算心率数据
* 参数：心率传感器采集到的数据
* 返回值：1 - 可以调用GetBloodpressureValue函数读取血压值  
*******************************************************/
uint8_t GetBloodpressure_PS_Value(void)
{
	return PS;
}
uint8_t GetBloodpressure_PD_Value(void)
{
	return PD;
}
void Clear_Blood_Pressure(void)
{		
	PS=0;
	PD=0;
	PPG_Pd=0;
	PPG_Ps=0;
	PPG_PS_Sum=0;
	PPG_PD_Sum=0;
	PPG_PS_average =0;
	PPG_PD_average =0;
	
}



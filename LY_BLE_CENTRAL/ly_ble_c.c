#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_bas.h"
#include "ble_hrs.h"
#include "ble_dis.h"
#include "ble_conn_params.h"
#include "sensorsim.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_freertos.h"
#include "app_timer.h"
#include "peer_manager.h"
#include "peer_manager_handler.h"
#include "bsp_btn_ble.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "fds.h"
#include "ble_conn_state.h"
#include "nrf_drv_clock.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_ble_scan.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "ly_ble.h"
#include "ly_ble_c.h"

#include "ly_ble_tus_c.h"

BLE_TUS_C_ARRAY_DEF(m_tus_c, NRF_SDH_BLE_CENTRAL_LINK_COUNT);        
NRF_BLE_SCAN_DEF(m_scan);                                                                        /**< Scanning module instance. */

/**@brief Names that the central application scans for, and that are advertised by the peripherals.
 *  If these are set to empty strings, the UUIDs defined below are used.
 */

static char const m_target_periph_name[] = "nut";


static ble_gap_scan_params_t m_scan_param =                 /**< Scan parameters requested for scanning and connection. */
{
	.extended = 0,
	.report_incomplete_evts = 0,
    .active        = 0x01,
    .interval      = NRF_BLE_SCAN_SCAN_INTERVAL,
    .window        = NRF_BLE_SCAN_SCAN_WINDOW,
    .filter_policy = BLE_GAP_SCAN_FP_ACCEPT_ALL,
    .timeout       = NRF_BLE_SCAN_SCAN_DURATION,
    .scan_phys     = BLE_GAP_PHY_1MBPS,
    .extended      = true,
};

static void scan_evt_handler(scan_evt_t const * p_scan_evt)
{
    ret_code_t err_code;
    ble_gap_evt_adv_report_t const * p_adv = 
                   p_scan_evt->params.filter_match.p_adv_report;
    ble_gap_scan_params_t    const * p_scan_param = 
                   p_scan_evt->p_scan_params;

    switch(p_scan_evt->scan_evt_id)
    {
        case NRF_BLE_SCAN_EVT_FILTER_MATCH:
        {
        	NRF_LOG_INFO("Find device, do connect");
            // Initiate connection.
            err_code = sd_ble_gap_connect(&p_adv->peer_addr,
                                          p_scan_param,
                                          &m_scan.conn_params,
                                          APP_BLE_CONN_CFG_TAG);
            APP_ERROR_CHECK(err_code);
        } break;

        case NRF_BLE_SCAN_EVT_CONNECTING_ERROR:
        {
            err_code = p_scan_evt->params.connecting_err.err_code;
            APP_ERROR_CHECK(err_code);
        } break;

		case NRF_BLE_SCAN_EVT_SCAN_TIMEOUT:
		{
			NRF_LOG_INFO("NRF_BLE_SCAN_EVT_SCAN_TIMEOUT\r\n");
		} break;

    	case NRF_BLE_SCAN_EVT_SCAN_REQ_REPORT:
    	{
    		NRF_LOG_INFO("NRF_BLE_SCAN_EVT_SCAN_REQ_REPORT\r\n");
    	} break;

    	case NRF_BLE_SCAN_EVT_CONNECTED:
    	{
    		NRF_LOG_INFO("NRF_BLE_SCAN_EVT_CONNECTED\r\n");
    	} break;

        default:
            break;
    }
}


/**@brief Function for initialization the scanning and setting the filters.
 */
static void scan_init(void)
{
    ret_code_t          err_code;
    nrf_ble_scan_init_t init_scan;

    memset(&init_scan, 0, sizeof(init_scan));

    init_scan.p_scan_param = &m_scan_param;
    //init_scan.connect_if_match = true;		/*Pay more attention to this parameter*/			
	init_scan.connect_if_match = false;
	init_scan.conn_cfg_tag     = APP_BLE_CONN_CFG_TAG;

    err_code = nrf_ble_scan_init(&m_scan, &init_scan, scan_evt_handler);
    APP_ERROR_CHECK(err_code);

    if (strlen(m_target_periph_name) != 0)
    {
        err_code = nrf_ble_scan_filter_set(&m_scan, 
                                           SCAN_NAME_FILTER, 
                                           m_target_periph_name);
        APP_ERROR_CHECK(err_code);
    }

    err_code = nrf_ble_scan_filters_enable(&m_scan, 
                                           NRF_BLE_SCAN_NAME_FILTER, 
                                           false);
    APP_ERROR_CHECK(err_code);

}

/**@brief Function for initializing the scanning.
 */
void scan_start(void)
{
    ret_code_t err_code;

    err_code = nrf_ble_scan_start(&m_scan);
    APP_ERROR_CHECK(err_code);
}

void scan_stop(void)
{	
    nrf_ble_scan_stop();
}

/**@brief Handles events coming from the TUS central module.
 *
 * @param[in] p_tus_c     The instance of TUS_C that triggered the event.
 * @param[in] p_tus_c_evt The TUS_C event.
 */
static void tus_c_evt_handler(ble_tus_c_t * p_tus_c, ble_tus_c_evt_t const * p_tus_c_evt)
{
	switch(p_tus_c_evt->evt_type)
	{
		default:
			break;
	}
    NRF_LOG_INFO("!!!");
}

static void tus_c_init(void)
{
	ret_code_t 		 err_code;
	ble_tus_c_init_t tus_c_init_obj;

	tus_c_init_obj.evt_handler = tus_c_evt_handler;

	for(uint32_t i = 0; i < NRF_SDH_BLE_CENTRAL_LINK_COUNT; i++)
	{
		err_code = ble_tus_c_init(&m_tus_c[i], &tus_c_init_obj);
		APP_ERROR_CHECK(err_code);
	}
}

/**@brief   Function for handling BLE events from the central application.
 *
 * @details This function parses scanning reports and initiates a connection to peripherals when a
 *          target UUID is found. It updates the status of LEDs used to report the central application
 *          activity.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 */
static void on_ble_central_evt(ble_evt_t const * p_ble_evt)
{
    ret_code_t            err_code;
    ble_gap_evt_t const * p_gap_evt = &p_ble_evt->evt.gap_evt;

    switch (p_ble_evt->header.evt_id)
    {
        // Upon connection, check which peripheral is connected, initiate DB
        // discovery, update LEDs status, and resume scanning, if necessary.
        case BLE_GAP_EVT_CONNECTED:
        {
            NRF_LOG_INFO("Connection 0x%x established, starting DB discovery.",
						p_gap_evt->conn_handle);

		    APP_ERROR_CHECK_BOOL(p_gap_evt->conn_handle < NRF_SDH_BLE_CENTRAL_LINK_COUNT);

			err_code = ble_tus_c_handles_assign(&m_tus_c[p_gap_evt->conn_handle], 
												p_gap_evt->conn_handle,
												NULL);
			APP_ERROR_CHECK(err_code);

			#if 1
			ly_ble_db_discovery_start(p_gap_evt->conn_handle);
			#else
			err_code = ble_db_discovery_start(&m_db_discovery[p_gap_evt->conn_handle],
											  p_gap_evt->conn_handle);

			if(err_code != NRF_ERROR_BUSY)
			{
				APP_ERROR_CHECK(err_code);
			}
			#endif

			if(ble_conn_state_central_conn_count() == NRF_SDH_BLE_CENTRAL_LINK_COUNT)
			{
			}
			else
			{
				scan_start();
			}
            
        } break; // BLE_GAP_EVT_CONNECTED

        // Upon disconnection, reset the connection handle of the peer that disconnected,
        // update the LEDs status and start scanning again.
        case BLE_GAP_EVT_DISCONNECTED:
        {
         	NRF_LOG_INFO("TUS central link 0x%x disconnected (reason: 0x%x)", 
						p_gap_evt->conn_handle,
						p_gap_evt->params.disconnected.reason);

			if(ble_conn_state_central_conn_count() == 0)
			{
				 
			}

			scan_start();
        } break; // BLE_GAP_EVT_DISCONNECTED

        case BLE_GAP_EVT_TIMEOUT:
        {
        	// APP initiates stop scan
            // No timeout for scanning is specified, so only connection attemps can timeout.
            if (p_gap_evt->params.timeout.src == BLE_GAP_TIMEOUT_SRC_CONN)
            {
                NRF_LOG_INFO("Connection Request timed out.");
            }
        } break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
        {
        	NRF_LOG_DEBUG("BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST.");
            // Accept parameters requested by peer.
            err_code = sd_ble_gap_conn_param_update(p_gap_evt->conn_handle,
                                        &p_gap_evt->params.conn_param_update_request.conn_params);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
        {
            NRF_LOG_DEBUG("PHY update request.");
            ble_gap_phys_t const phys =
            {
                .rx_phys = BLE_GAP_PHY_AUTO,
                .tx_phys = BLE_GAP_PHY_AUTO,
            };
            err_code = sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle, &phys);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTC_EVT_TIMEOUT:
            // Disconnect on GATT Client timeout event.
            NRF_LOG_DEBUG("GATT Client Timeout.");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server timeout event.
            NRF_LOG_DEBUG("GATT Server Timeout.");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break;

        default:
            // No implementation needed.
            break;
    }
}


void ly_ble_c_db_disc_handler(ble_db_discovery_evt_t * p_evt)
{	
	ble_tus_c_on_db_disc_evt(&m_tus_c[p_evt->conn_handle], p_evt);
}

void ly_ble_c_init(ly_ble_c_t *p_ly_ble_c)
{
	p_ly_ble_c->on_ble_central_evt = on_ble_central_evt;
	scan_init();
	tus_c_init();
}

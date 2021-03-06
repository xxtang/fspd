#include <stdio.h>
#include <stdlib.h>

#ifndef P2P_API
#define P2P_API

#define P2P_LIB_VERSION "1.1.17"

typedef void * REND_EPT_HANDLE;
typedef void * REND_CONN_HANDLE;
typedef int P2P_endpoint_event(REND_EPT_HANDLE endpoint, int event);

typedef enum {
    P2P_LOG_TYPE_NONE,
    P2P_LOG_TYPE_FILE,
    P2P_LOG_TYPE_SCREEN,
    P2P_LOG_TYPE_MAX,
}P2P_LOG_TYPE;

typedef enum {
	ENDPOINT_INITIAL,
	ENDPOINT_REGISTERING,
	ENDPOINT_REGISTER_FAIL,
	ENDPOINT_REGISTER_OK,
}endpoint_status;

typedef enum {
	CONNECTION_INIT,
	CONNECTION_REQUEST,
	CONNECTION_PING,
	CONNECTION_FAILED,
	CONNECTION_OK,
	CONNECTION_POK,
}rendezvous_connection_status;

typedef enum {
	ENDPOINT_EVENT_NAT_CHANGE = 0x1,
	ENDPOINT_EVENT_CONN_FAIL = 0x2,
	ENDPOINT_EVENT_CONN_OK = 0x4,
	ENDPOINT_EVENT_FD_CLOSE = 0x8,
}p2p_endpoint_event_bit;

int p2p_init(char *log_path, char *app_name, P2P_LOG_TYPE log_type, int log_level, char *server, int server_port);

REND_EPT_HANDLE new_rendezvous_endpoint(char *cid, char *service, char *oid, char *ic, char *key, int udp_fd);
int rendezvous_endpoint_reg(REND_EPT_HANDLE endpoint);
int rendezvous_endpoint_eventCallbacks(REND_EPT_HANDLE endpoint, int event_mask, P2P_endpoint_event *ev);
void free_rendezvous_endpoint(REND_EPT_HANDLE endpoint);
int get_rendezvous_endpoint(REND_EPT_HANDLE endpoint, int *status, char *cid, char *ed, char *ped);
int get_rendezvous_endpoint_error(REND_EPT_HANDLE endpoint, int *status, int *error_code);
int get_rendezvous_endpoint_event(REND_EPT_HANDLE endpoint, int *event, int reset);
int rendezvous_endpoint_query(REND_EPT_HANDLE endpoint, char* req, char* resp);

REND_CONN_HANDLE new_rendezvous_connection(REND_EPT_HANDLE my_endpoint, char *tid, char *service, char *toid, char *tic);
void free_rendezvous_connection(REND_CONN_HANDLE conn);
int get_rendezvous_connection(REND_CONN_HANDLE conn, int *status, char *r_ed, char *r_ped);
int get_rendezvous_connection_attr(REND_CONN_HANDLE conn, char *attr, char *value);
int get_rendezvous_connection_error(REND_CONN_HANDLE conn, int *status, int *error_code);

int handle_rendezvous_packet(int udp_fd, char *udp_message, struct sockaddr_in *peer_addr);
int rendezvous_status_handle(void); //周期调用
int set_p2p_reg_keep_interval(int interval);
void set_p2p_option(int crypt, int debug);
int set_p2p_config(char *param, char *value);

int get_deviceId_key(char *id, char *key);
int get_deviceId_byMac(char *mac, char *id);
void show_endpoints(void);
void show_connections(void);
void dump_p2p_lib_global(int debug);
#endif

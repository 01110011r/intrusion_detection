//
// Created by samandar on 1/19/25.
//

typedef struct
{
    int id;
    char timestamp[20];
    char attack_type[50];
    char source_ip[30];
    char destination_ip[30];
    char protocol[15];
    char details[255];
} ILogInfo;

#ifndef INTRUSION_DETECTION_DB
#define INTRUSION_DETECTION_DB
int connect_db();
int create_schema(const char *schema_query);
int insert_data(const char *query);
int insert_data1(ILogInfo *log);
int get_logs(ILogInfo * logs, int max_logs);
void close_db();
#endif //INTRUSION_DETECTION_DB
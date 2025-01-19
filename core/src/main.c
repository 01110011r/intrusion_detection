//
// Created by samandar on 1/12/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analyze.h"
#include "db.h"

void initialize_system();

int main()
{
    printf("Intrusion Detection System (IDS) is starting...\n");

    // initialize
    initialize_system();

    // db connection
    if (connect_db() != 0)
    {
        return 1;
    }

    // create schema
    const char *schema_query = "CREATE TABLE IF NOT EXISTS intrusion_logs ("
                               "id SERIAL PRIMARY KEY, "
                               "timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                               "source_ip VARCHAR(45), "
                               "destination_ip VARCHAR(45), "
                               "protocol VARCHAR(10), "
                               "details TEXT);";

    if (create_schema(schema_query) != 0)
    {
        close_db();
        return 1;
    }

    // aniqlangan intrusionni db ga saqlash.
    //  const char *query = "INSERT INTO intrusion_logs(timestamp, attack_type, source_ip, destination_ip, protocol, details) VALUES(NOW(), 'DDoS', 'source_ip', 'destination_ip', 'https', 'testing')";
    //  if (insert_data(query) != 0)
    //  {
    //      close_db();
    //      return 1;
    //  }
    ILogInfo new_log;
    strcpy(new_log.attack_type, "SQL injection");
    strcpy(new_log.source_ip, "source_ip");
    strcpy(new_log.destination_ip, "destination_ip");
    strcpy(new_log.protocol, "protocol");
    strcpy(new_log.details, "details");

    if (insert_data1(&new_log) == 0)
    {
        printf("Log sucessfully added.\n");
    }

    // logni o'qish.
    ILogInfo logs[10];
    int count = get_logs(logs, 10);
    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            printf("Log ID: %d\n, Timestamp: %s\n, Source IP: %s\n, Destination IP: %s\n, Protocol: %s\n, Details: %s\n",
                   logs[i].id, logs[i].timestamp, logs[i].source_ip, logs[i].destination_ip, logs[i].protocol, logs[i].details);
        }
    }

    // Analyzing network traffic
    analyze_traffic();

    close_db();
    printf("IDS is ready to detect intrusions.\n");
    return 0;
}

// IDS initialization
void initialize_system()
{
    printf("Initializing IDS...\n");
    // IDS initialization code goes here
    printf("IDS is initialized.\n");
}

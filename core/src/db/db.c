//
// Created by samandar on 1/13/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>

#include "db.h"

PGconn *conn = NULL;

int connect_db()
{
    const char *conninfo = "dbname=intrusion_detection user=postgres password=postgres host=localhost port=5432";

    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "PostgreSQL ulanishi xato: %s", PQerrorMessage(conn));
        return 1;
    };

    printf("Postgres bilan muvaffaqiyatli ulanish.\n");
    return 0;
}

int create_schema(const char *schema_query)
{

    PGresult *res = PQexec(conn, schema_query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Schema yaratishda xato: %s", PQerrorMessage(conn));
        PQclear(res);
        return 1;
    }

    PQclear(res);
    return 0;
}

int insert_data(const char *query)
{
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Sorov xatosi: %s", PQerrorMessage(conn));
        PQclear(res);
        return 1;
    };

    PQclear(res);
    return 0;
}

int insert_data1(ILogInfo *log)
{
    char query[512];
    snprintf(query, sizeof(query),
             "INSERT INTO intrusion_logs(timestamp, attack_type, source_ip, destination_ip, protocol, details)"
             "VALUES(NOW(), '%s', '%s', '%s', '%s', '%s');",
             log->attack_type, log->source_ip, log->destination_ip, log->protocol, log->details);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Failed to insert log: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return -1;
    }
    PQclear(res);
    return 0;
}

int get_logs(ILogInfo *logs, int max_logs)
{
    char query[] = "SELECT * FROM intrusion_logs";
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch logs: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return -1;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows && i < max_logs; i++)
    {
        logs[i].id = atoi(PQgetvalue(res, i, 0));
        strncpy(logs[i].timestamp, PQgetvalue(res, i, 1), sizeof(logs[i].timestamp));
        strncpy(logs[i].attack_type, PQgetvalue(res, i, 2), sizeof(logs[i].attack_type));
        strncpy(logs[i].source_ip, PQgetvalue(res, i, 3), sizeof(logs[i].source_ip));
        strncpy(logs[i].destination_ip, PQgetvalue(res, i, 4), sizeof(logs[i].destination_ip));
        strncpy(logs[i].protocol, PQgetvalue(res, i, 5), sizeof(logs[i].protocol));
        strncpy(logs[i].details, PQgetvalue(res, i, 6), sizeof(logs[i].details));
    }
    PQclear(res);
    return rows;
}

void close_db()
{
    PQfinish(conn);
    printf("PostgreSQL ulanishi uzuldi.\n");
}
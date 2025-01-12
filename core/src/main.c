//
// Created by samandar on 1/12/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "analyze.h"

void initialize_system();

int main() {
    printf("Intrusion Detection System (IDS) is starting...\n");
    initialize_system();

    //Analyzing network traffic
    analyze_traffic();


    printf("IDS is ready to detect intrusions.\n");
    return 0;
}

//IDS initialization
void initialize_system() {
    printf("Initializing IDS...\n");
    // IDS initialization code goes here
    printf("IDS is initialized.\n");
}

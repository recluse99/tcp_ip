//
// Created by root on 23-3-2.
//

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {

    struct sockaddr_in addr1, addr2;

    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);

    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);

    strcpy(str_arr, str_ptr);


    printf("dotted-decimal notation1: %s \n", str_arr);
    printf("dotted-decimal notation1: %s \n", str_ptr);

    printf("%s length is : %lu \n", str_arr, strlen(str_arr));


    printf("dasd");


    return 0;
}






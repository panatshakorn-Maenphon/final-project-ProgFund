#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char booker[MAX][50];
char package[MAX][50];
char date[MAX][20];
int people[MAX];
int count = 0;


void loadCSV() {
    FILE *fp = fopen("booking.csv", "r");
    if (!fp) return;

    while (fscanf(fp, "%49[^,],%49[^,],%19[^,],%d\n",
                  booker[count], package[count], date[count], &people[count]) == 4) {
        count++;
    }
    fclose(fp);
}


void saveCSV() {
    FILE *fp = fopen("booking.csv", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%d\n",
                booker[i], package[i], date[i], people[i]);
    }
    fclose(fp);
}


void displayAll() {
    for (int i = 0; i < count; i++) {
        printf("%d. %s | %s | %s | %d คน\n",
               i + 1, booker[i], package[i], date[i], people[i]);
    }
}


void addBooking() {
    printf("ชื่อลูกค้า: ");
    scanf(" %[^\n]", booker[count]);
    printf("แพ็คเกจทัวร์: ");
    scanf(" %[^\n]", package[count]);
    printf("วันที่จอง: ");
    scanf(" %[^\n]", date[count]);
    printf("จำนวนคน: ");
    scanf("%d", &people[count]);
    count++;
    saveCSV();
}


void searchBooking() {
    char name[50];
    printf("กรอกชื่อที่ต้องการค้นหา: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(booker[i], name) == 0) {
            printf("เจอ: %s | %s | %s | %d คน\n",
                   booker[i], package[i], date[i], people[i]);
            return;
        }
    }
    printf("ไม่พบข้อมูล\n");
}


void updateBooking() {
    char name[50];
    printf("กรอกชื่อที่ต้องการแก้ไข: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(booker[i], name) == 0) {
            printf("จำนวนคนใหม่: ");
            scanf("%d", &people[i]);
            saveCSV();
            printf("อัพเดทเรียบร้อย\n");
            return;
        }
    }
    printf("ไม่พบข้อมูล\n");
}


void deleteBooking() {
    char name[50];
    printf("กรอกชื่อที่ต้องการลบ: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(booker[i], name) == 0) {
            for (int j = i; j < count - 1; j++) {
                strcpy(booker[j], booker[j + 1]);
                strcpy(package[j], package[j + 1]);
                strcpy(date[j], date[j + 1]);
                people[j] = people[j + 1];
            }
            count--;
            saveCSV();
            printf("ลบเรียบร้อย\n");
            return;
        }
    }
    printf("ไม่พบข้อมูล\n");
}


void menu() {
    int ch;
    do {
        printf("\n===== เมนูจองทัวร์ =====\n");
        printf("1. แสดงข้อมูลทั้งหมด\n");
        printf("2. เพิ่มข้อมูลการจอง\n");
        printf("3. ค้นหาข้อมูล\n");
        printf("4. แก้ไขจำนวนคน\n");
        printf("5. ลบข้อมูล\n");
        printf("0. ออก\n");
        printf("เลือก: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: displayAll(); break;
            case 2: addBooking(); break;
            case 3: searchBooking(); break;
            case 4: updateBooking(); break;
            case 5: deleteBooking(); break;
        }
    } while (ch != 0);
}

int main() {
    loadCSV();
    menu();
    return 0;
}

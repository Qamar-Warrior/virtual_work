#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_PATH "/etc/ssh/sshd_config"
#define BACKUP_PATH "/etc/ssh/sshd_config.bak"

void backup_config() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cp %s %s", CONFIG_PATH, BACKUP_PATH);
    system(cmd);
}

void restore_config() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cp %s %s", BACKUP_PATH, CONFIG_PATH);
    system(cmd);
}

void set_root_login(int enable) {
    FILE *fp = fopen(CONFIG_PATH, "r+");
    if (!fp) {
        perror("Failed to open config file");
        exit(1);
    }

    FILE *tmp = fopen("/tmp/sshd_config.tmp", "w");
    if (!tmp) {
        perror("Failed to open temp file");
        fclose(fp);
        exit(1);
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "PermitRootLogin")) {
            fprintf(tmp, "PermitRootLogin %s\n", enable ? "yes" : "no");
        } else {
            fputs(line, tmp);
        }
    }

    fclose(fp);
    fclose(tmp);

    system("mv /tmp/sshd_config.tmp /etc/ssh/sshd_config");
}

void restart_ssh() {
    system("systemctl restart sshd");
}

int main() {
    int choice;
    printf("Choose an option:\n");
    printf("1. Enable remote root login\n");
    printf("2. Restore original config\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            backup_config();
            set_root_login(1);
            restart_ssh();
            printf("Remote root login enabled.\n");
            break;
        case 2:
            restore_config();
            restart_ssh();
            printf("Configuration restored.\n");
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

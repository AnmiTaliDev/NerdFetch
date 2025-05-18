#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef __linux__
#include <sys/sysinfo.h>
#endif

// Определяем цвета ANSI
#define BOLD "\033[1m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define GREY "\033[90m"
#define RESET "\033[0m"

// Структура для хранения информации
typedef struct {
    char os[100];
    char kernel[50];
    char packages[50];
    char packageManager[20];
    char uptime[50];
    char memory[100];
    char hostname[100];
    char username[50];
    
    // Иконки для различных шрифтов
    char osi[8];
    char ki[8];
    char ri[8];
    char pi[8];
    char ui[8];
    char ci[8];
} SystemInfo;

// Функции для получения системной информации
void getOSInfo(SystemInfo *info);
void getKernelInfo(SystemInfo *info);
void getPackageInfo(SystemInfo *info);
void getUptimeInfo(SystemInfo *info);
void getMemoryInfo(SystemInfo *info);
void getHostInfo(SystemInfo *info);
void getUserInfo(SystemInfo *info);
void setIcons(SystemInfo *info, char *font);
void printOutput(SystemInfo *info);
void readOSRelease(SystemInfo *info);

int main(int argc, char *argv[]) {
    SystemInfo info;
    char font[10] = "nerd"; // По умолчанию nerd шрифт
    
    // Обработка аргументов командной строки
    if (argc > 1) {
        if (strcmp(argv[1], "-p") == 0) {
            strcpy(font, "phosphor");
        } else if (strcmp(argv[1], "-c") == 0) {
            strcpy(font, "cozette");
        } else if (strcmp(argv[1], "-e") == 0) {
            strcpy(font, "emoji");
        } else if (strcmp(argv[1], "-v") == 0) {
            printf("NerdFetch 8.3.1\n");
            return 0;
        } else if (strcmp(argv[1], "-h") == 0) {
            printf("Flags:\n-c: Cozette font\n-p: Phosphor font\n-e: Emoji font\n-v: Version\n");
            return 0;
        }
    }
    
    // Получаем и устанавливаем иконки в зависимости от выбранного шрифта
    setIcons(&info, font);
    
    // Получаем информацию о системе
    getOSInfo(&info);
    getKernelInfo(&info);
    getPackageInfo(&info);
    getUptimeInfo(&info);
    getMemoryInfo(&info);
    getHostInfo(&info);
    getUserInfo(&info);
    
    // Выводим полученную информацию
    printOutput(&info);
    
    return 0;
}

void setIcons(SystemInfo *info, char *font) {
    if (strcmp(font, "nerd") == 0) {
        strcpy(info->osi, "");
        strcpy(info->ki, "");
        strcpy(info->ri, "󰍛");
        strcpy(info->pi, "󰏔");
        strcpy(info->ui, "󰅶");
        strcpy(info->ci, "");
    } else if (strcmp(font, "phosphor") == 0) {
        strcpy(info->osi, "");
        strcpy(info->ki, "");
        strcpy(info->ri, "");
        strcpy(info->pi, "");
        strcpy(info->ui, "");
        strcpy(info->ci, "");
    } else if (strcmp(font, "cozette") == 0) {
        strcpy(info->osi, "");
        strcpy(info->ki, "♥");
        strcpy(info->ri, "");
        strcpy(info->pi, "");
        strcpy(info->ui, "");
        strcpy(info->ci, "");
    } else if (strcmp(font, "emoji") == 0) {
        strcpy(info->osi, "🐧");
        strcpy(info->ki, "💓");
        strcpy(info->ri, "🐐");
        strcpy(info->pi, "📦");
        strcpy(info->ui, "☕");
        strcpy(info->ci, "🎨");
    }
}

void getOSInfo(SystemInfo *info) {
    struct utsname sys_info;
    uname(&sys_info);
    
    if (strcmp(sys_info.sysname, "Linux") == 0) {
        readOSRelease(info);
    } else if (strcmp(sys_info.sysname, "Darwin") == 0) {
        sprintf(info->os, "macOS %s", sys_info.release);
        strcpy(info->osi, "");
    } else if (strcmp(sys_info.sysname, "FreeBSD") == 0) {
        sprintf(info->os, "FreeBSD %s", sys_info.release);
        strcpy(info->osi, "");
    } else if (strcmp(sys_info.sysname, "OpenBSD") == 0) {
        sprintf(info->os, "OpenBSD %s", sys_info.release);
        strcpy(info->osi, "");
    } else if (strcmp(sys_info.sysname, "NetBSD") == 0) {
        sprintf(info->os, "NetBSD %s", sys_info.release);
        strcpy(info->osi, "󰉀");
    } else {
        strcpy(info->os, "Unix-like");
    }
}

void readOSRelease(SystemInfo *info) {
    FILE *fp = fopen("/etc/os-release", "r");
    if (fp != NULL) {
        char line[256];
        char name[100] = "";
        
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
                // Удаляем кавычки
                char *start = strchr(line, '"');
                if (start) {
                    start++;
                    char *end = strchr(start, '"');
                    if (end) {
                        *end = '\0';
                        strcpy(name, start);
                    }
                }
                break;
            }
        }
        fclose(fp);
        
        if (strlen(name) > 0) {
            strcpy(info->os, name);
        } else {
            strcpy(info->os, "Linux");
        }
    }
}

void getKernelInfo(SystemInfo *info) {
    struct utsname sys_info;
    uname(&sys_info);
    
    // Берем только основную версию ядра без дополнительной информации
    char *dash = strchr(sys_info.release, '-');
    if (dash) {
        *dash = '\0';
    }
    
    strcpy(info->kernel, sys_info.release);
}

void getPackageInfo(SystemInfo *info) {
    // Упрощенная версия - просто подсчитываем количество файлов в /usr/bin как пример
    DIR *dir;
    struct dirent *ent;
    int count = 0;
    
    if ((dir = opendir("/usr/bin")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            count++;
        }
        closedir(dir);
    }
    
    sprintf(info->packages, "%d", count);
    strcpy(info->packageManager, "bin");
}

void getUptimeInfo(SystemInfo *info) {
#ifdef __linux__
    struct sysinfo s_info;
    sysinfo(&s_info);
    
    long uptime = s_info.uptime;
    int days = uptime / (60*60*24);
    int hours = (uptime / (60*60)) % 24;
    int minutes = (uptime / 60) % 60;
    
    if (days > 0) {
        sprintf(info->uptime, "%d day%s, %d hour%s, %d min%s", 
                days, days > 1 ? "s" : "", 
                hours, hours > 1 ? "s" : "", 
                minutes, minutes > 1 ? "s" : "");
    } else if (hours > 0) {
        sprintf(info->uptime, "%d hour%s, %d min%s", 
                hours, hours > 1 ? "s" : "", 
                minutes, minutes > 1 ? "s" : "");
    } else {
        sprintf(info->uptime, "%d min%s", 
                minutes, minutes > 1 ? "s" : "");
    }
#else
    // Для других ОС - базовое решение
    strcpy(info->uptime, "Unknown");
#endif
}

void getMemoryInfo(SystemInfo *info) {
#ifdef __linux__
    struct sysinfo s_info;
    sysinfo(&s_info);
    
    long total_mem = s_info.totalram * s_info.mem_unit / (1024 * 1024);
    long free_mem = s_info.freeram * s_info.mem_unit / (1024 * 1024);
    long used_mem = total_mem - free_mem;
    int percent = (used_mem * 100) / total_mem;
    
    sprintf(info->memory, "%ld/%ld MiB (%d%%)", used_mem, total_mem, percent);
#else
    // Для других операционных систем
    strcpy(info->memory, "Memory info not available");
#endif
}

void getHostInfo(SystemInfo *info) {
    struct utsname sys_info;
    if (uname(&sys_info) != 0) {
        strcpy(info->hostname, "unknown-host");
    } else {
        strncpy(info->hostname, sys_info.nodename, sizeof(info->hostname) - 1);
        info->hostname[sizeof(info->hostname) - 1] = '\0';
    }
}

void getUserInfo(SystemInfo *info) {
    char *user = getenv("USER");
    if (!user) {
        user = getenv("LOGNAME");
    }
    if (!user) {
        strcpy(info->username, "user");
    } else {
        strcpy(info->username, user);
    }
}

void printOutput(SystemInfo *info) {
    char *lc = RESET BOLD MAGENTA; // labels
    char *nc = RESET BOLD YELLOW;  // user
    char *hn = RESET BOLD BLUE;    // hostname
    char *ic = RESET GREEN;        // info
    char *c0 = RESET GREY;         // first color
    char *c1 = RESET WHITE;        // second color
    char *c2 = RESET YELLOW;       // third color
    
    printf("\n");
    printf("%s      ___     %s%s%s@%s%s%s%s \n", c0, nc, info->username, RED, RESET, hn, info->hostname, RESET);
    printf("%s     (%s.. %s\\    %s%s  %s%s%s\n", c0, c1, c0, lc, info->osi, ic, info->os, RESET);
    printf("%s     (%s<> %s|    %s%s  %s%s%s\n", c0, c2, c0, lc, info->ki, ic, info->kernel, RESET);
    printf("%s    /%s/  \\ %s\\   %s%s  %s%s%s\n", c0, c1, c0, lc, info->ri, ic, info->memory, RESET);
    printf("%s   ( %s|  | %s/|  %s%s  %s%s (%s)%s\n", c0, c1, c0, lc, info->pi, ic, info->packages, info->packageManager, RESET);
    printf("%s  _%s/\\ %s__)%s/%s_%s)  %s%s  %s%s%s\n", c2, c0, c1, c0, c2, c0, lc, info->ui, ic, info->uptime, RESET);
    printf("%s  \\/%s-____%s\\/%s   %s%s  %s███%s███%s███%s███%s███%s███%s\n", 
           c2, c0, c2, RESET, lc, info->ci, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, RESET);
    printf("\n");
}
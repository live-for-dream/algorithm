#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int full_array(char *str, int len, char *pre_str, int pre_len) {
    int   i;
    int   ret;
    char *tmp_str;
    char *new_str;
    char *new_prestr;
    
    if (len + pre_len <= 1) {
        return -1;
    }
    if (len == 1) {
        printf("%s%s\n", pre_str, str);
        return 0;
    }
    
    new_str = (char *)malloc(sizeof(char) * (len));
    if (!new_str) {
        goto FAIL;
    }
    new_prestr = (char *)malloc(sizeof(char) * (pre_len + 2));

    if (!new_prestr) {
        goto STR_FAIL;
    }

    snprintf(new_str, len, "%s", str + 1);
    if (pre_len > 0) {
        sprintf(new_prestr, "%s%c", pre_str, str[0]);
    } else {
        new_prestr[0] = str[0];
    }
    new_prestr[pre_len + 1] = '\0';
    ret = full_array(new_str, len - 1, new_prestr, pre_len + 1);
    if (ret) {
        goto PRESTR_FAIL;
    }
    
    for (i = 1; i < len - 1; i++) {
        //tmp_str = str + i + 1;
        snprintf(new_str, i + 1, "%s", str);
        tmp_str = new_str + i;
        snprintf(tmp_str, len - i, "%s", str + i + 1);
        new_prestr[pre_len] = str[i];
        new_prestr[pre_len + 1] = '\0';
        ret = full_array(new_str, len - 1, new_prestr, pre_len + 1);
        if (ret) {
            goto PRESTR_FAIL;
        }
    }
    
    snprintf(new_str, len, "%s", str);
    new_prestr[pre_len] = str[i];
    new_prestr[pre_len + 1] = '\0';
    ret = full_array(new_str, len - 1, new_prestr, pre_len + 1);
    if (ret) {
        goto PRESTR_FAIL;
    }

    return 0;

PRESTR_FAIL:
    free(new_prestr);
STR_FAIL:
    free(new_str);
FAIL:
    return -1;    

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: ./full_array <string>\n");
        return -1;
    }

    int         len;
    int         pre_len = 0;
    char       *str;
    char       *pre_str = NULL;
    int         ret;

    str = argv[1];
    len = strlen(str);
    ret = full_array(str, len, pre_str, pre_len);
    if (ret) {
        printf("some error\n");
        return -1;
    }

    return 0;
}

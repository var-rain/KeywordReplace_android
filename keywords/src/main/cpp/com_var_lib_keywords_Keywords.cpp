#include "com_var_lib_keywords_Keywords.h"

void Java_com_var_lib_keywords_Keywords_loadDict(JNIEnv *env, jclass clazz, jstring str) {
    /* 将JAVA的字符串转换为C语言的字符串 */
    const char *file_name = (env)->GetStringUTFChars(str, JNI_FALSE);
    /* 只读形式打开文件 */
    FILE *pDict = fopen(file_name, "r");
    /* 判断文件是否成功打开 */
    if (pDict == NULL) {
        LOGE("[%s] File open error!", file_name);
    } else {
        /* 获取文件大小 */
        fseek(pDict, 0, SEEK_END);
        long size = ftell(pDict);
        fseek(pDict, 0, SEEK_SET);
        /* 开辟内存 */
        file = (char *) (malloc(sizeof(char) * size));
        /* 读入内存 */
        int bSize = (int) fread(file, sizeof(char), sizeof(char) * size, pDict);
        LOGI("load %d byte to memory.", bSize);
    }
    /* 关闭文件流 */
    if (pDict != NULL) {
        fclose(pDict);
    }
    /* 释放字符串 */
    (env)->ReleaseStringUTFChars(str, file_name);
}

jboolean Java_com_var_lib_keywords_Keywords_hasKeywords(JNIEnv *env, jclass clazz, jstring str) {
    /* 默认没有匹配的关键字 */
    jboolean hasKeywords = JNI_FALSE;
    /* 文件存在判断 */
    if (file == NULL) {
        LOGE("Not load dictionary file!");
        return hasKeywords;
    }
    /* 将JAVA的字符串转换为C语言的字符串 */
    const char *source = (env)->GetStringUTFChars(str, JNI_FALSE);
    /* 字典总大小 */
    int len = (int) strlen(file);
    /* 遍历字典，取出单个字符组成字符串 */
    for (int i = 0; i < len; ++i) {
        /* 取出字符 */
        char ch = file[i];
        /* 如果遇到换行符 */
        if (ch == '\n') {
            /* 判断字符串是否包含另一个字符串 */
            if (strstr(source, buff) != NULL) {
                /* 如果包含，修改标记 */
                hasKeywords = JNI_TRUE;
                /* 清空字符串数组 */
                memset(buff, 0, sizeof(buff));
                break;
            }
            /* 清空字符串数组 */
            memset(buff, 0, sizeof(buff));
        } else {
            /* 叠加字符串 */
            buff[strlen(buff)] = ch;
        }
    }
    /* 释放字符串 */
    (env)->ReleaseStringUTFChars(str, source);
    /* 返回是否包含 */
    return hasKeywords;
}

jstring
Java_com_var_lib_keywords_Keywords_replaceKeywords(JNIEnv *env, jclass clazz, jstring str,
                                                   jchar ch) {
    /* 文件存在判断 */
    if (file == NULL) {
        LOGE("Not load dictionary file!");
        return str;
    }
    /* 将JAVA的字符串转换为C语言的字符串 */
    char *source = const_cast<char *>((env)->GetStringUTFChars(str, JNI_FALSE));
    /* 字典总大小 */
    int len = (int) strlen(file);
    /* 遍历字典，取出单个字符组成字符串 */
    for (int i = 0; i < len; ++i) {
        /* 取出字符 */
        char c = file[i];
        /* 如果遇到换行符 */
        if (c == '\n') {
            /* 定义起始索引位置 */
            int index;
            /* 计算匹配字符串的起始索引位置 */
            while ((index = findCharsIndex(source, buff)) != -1) {
                /* 遍历源字符串 */
                for (int p = 0; p < strlen(buff); ++p) {
                    /* 替换为匹配字符串长度的目标字符 */
                    source[index + p] = (char) ch;
                }
            }
            /* 清空字符串数组 */
            memset(buff, 0, sizeof(buff));
        } else {
            /* 叠加字符串 */
            buff[strlen(buff)] = c;
        }
    }
    /* 释放字符串 */
    (env)->ReleaseStringUTFChars(str, source);
    /* 创建jstring类型的字符串并返回 */
    return (env)->NewStringUTF(source);
}

void
Java_com_var_lib_keywords_Keywords_destroy(JNIEnv *env, jclass type) {
    if (file != NULL) {
        free(file);
        LOGI("Dictionary freed from memory.");
    }
}

int findCharsIndex(char *source, char *target) {
    /* 获取匹配字符串 */
    char *ss = strstr(source, target);
    /* 匹配字符串不为空则返回匹配字符串在源字符串中的起始索引位置 */
    if (ss != NULL) {
        return (int) (strlen(source) - strlen(ss));
    }
    /* 为空则返回-1 */
    return -1;
}
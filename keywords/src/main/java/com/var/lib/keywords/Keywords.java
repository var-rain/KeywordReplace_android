package com.var.lib.keywords;

/**
 * 关键词替换
 *
 * @author var.
 * @date 2018/7/19.
 */
public class Keywords {

    /* 加载动态库 */
    static {
        System.loadLibrary("Keywords");
    }

    /**
     * 加载关键词字典
     *
     * @param path 字典路径
     */
    public native static void loadDict(String path);

    /**
     * 判断字符串中是否包含关键词
     *
     * @param str 字符串
     * @return 如果包含关键词则返回true，不包含关键词则返回false
     */
    public native static boolean hasKeywords(String str);

    /**
     * 替换关键词
     *
     * @param str 字符串
     * @param ch  替换的目标字符
     * @return 返回替换后的字符串
     */
    public native static String replaceKeywords(String str, char ch);

    /**
     * 回收内存，避免内存泄漏,建议在程序退出的时候调用此方法
     */
    public native static void destroy();
}

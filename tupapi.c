#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include "php.h"
#include "php_ini.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"
#include "ext/standard/info.h"

#include "./include/tup_c.h"
#include "./include/tars_c.h"
#include "./include/php_tupapi.h"
#include "./include/ttars.h"


zend_class_entry *tup_ce;
zend_class_entry *tup_exception_ce;
zend_class_entry *tars_ce;
zend_class_entry *tars_struct_ce;
zend_class_entry *tars_vector_ce;
zend_class_entry *tars_map_ce;

// https://www.laruence.com/2020/02/27/5213.html
// tup_exception __construct
ZEND_BEGIN_ARG_INFO_EX(tup_exception___construct_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, msg)
    ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()

// tup putVector
ZEND_BEGIN_ARG_INFO_EX(tup_put_vector_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_OBJ_INFO(0, clazz, \\TARS_Vector, 0)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup getVector
ZEND_BEGIN_ARG_INFO_EX(tup_get_vector_arginfo, 0, 0, 3)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_OBJ_INFO(0, clazz, \\TARS_Vector, 0)
    ZEND_ARG_INFO(0, buf)
    ZEND_ARG_INFO(0, is_require)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup putMap
ZEND_BEGIN_ARG_INFO_EX(tup_put_map_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_OBJ_INFO(0, clazz, \\TARS_Map, 0)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup getMap
ZEND_BEGIN_ARG_INFO_EX(tup_get_map_arginfo, 0, 0, 3)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_OBJ_INFO(0, clazz, \\TARS_Map, 0)
    ZEND_ARG_INFO(0, buf)
    ZEND_ARG_INFO(0, is_require)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup putStruct
ZEND_BEGIN_ARG_INFO_EX(tup_put_struct_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_OBJ_INFO(0, clazz, \\TARS_Struct, 0)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup getStruct
ZEND_BEGIN_ARG_INFO_EX(tup_get_struct_arginfo, 0, 0, 3)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_OBJ_INFO(0, clazz, \\TARS_Struct, 0)
    ZEND_ARG_INFO(0, buf)
    ZEND_ARG_INFO(0, is_require)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup encode
ZEND_BEGIN_ARG_INFO_EX(tup_encode_arginfo, 0, 0, 10)
    ZEND_ARG_INFO(0, iVersion)
    ZEND_ARG_INFO(0, iRequestId)
    ZEND_ARG_INFO(0, servantName)
    ZEND_ARG_INFO(0, funcName)
    ZEND_ARG_INFO(0, cPacketType)
    ZEND_ARG_INFO(0, iMessageType)
    ZEND_ARG_INFO(0, iTimeout)
    ZEND_ARG_ARRAY_INFO(0, contexts, 0)
    ZEND_ARG_ARRAY_INFO(0, statuses, 0)
    ZEND_ARG_ARRAY_INFO(0, inbuf_arr, 0)
ZEND_END_ARG_INFO()

// tup decode
ZEND_BEGIN_ARG_INFO_EX(tup_decode_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, respBuffer)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup encodeRspPacket
ZEND_BEGIN_ARG_INFO_EX(tup_encode_rsp_packet_arginfo, 0, 0, 8)
    ZEND_ARG_INFO(0, iVersion)
    ZEND_ARG_INFO(0, cPacketType)
    ZEND_ARG_INFO(0, iMessageType)
    ZEND_ARG_INFO(0, iRequestId)
    ZEND_ARG_INFO(0, iRet)
    ZEND_ARG_INFO(0, sResultDesc)
    ZEND_ARG_ARRAY_INFO(0, inbuf_arr, 0)
    ZEND_ARG_ARRAY_INFO(0, statuses, 0)
ZEND_END_ARG_INFO()

// tup decodeReqPacket
ZEND_BEGIN_ARG_INFO_EX(tup_decode_req_packet_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, respBuffer)
ZEND_END_ARG_INFO()

// put common
ZEND_BEGIN_ARG_INFO_EX(put_common_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, value)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// get common
ZEND_BEGIN_ARG_INFO_EX(get_common_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, buf)
    ZEND_ARG_INFO(0, is_require)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup putString
ZEND_BEGIN_ARG_INFO_EX(tup_put_string_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, value)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

// tup getString
ZEND_BEGIN_ARG_INFO_EX(tup_get_string_arginfo, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, buf)
    ZEND_ARG_INFO(0, is_require)
    ZEND_ARG_INFO(0, iVersion)
ZEND_END_ARG_INFO()

/* {{{ ttup_exception_methods[]
 *
 * Every user visible function must have an entry in ttup_functions[].
 */
zend_function_entry tup_exception_methods[] = {
    PHP_ME(tup_exception, __construct, tup_exception___construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};
/* }}} */


/* {{{ tup_methods[]
 *
 * Every user visible function must have an entry in ttup_functions[].
 */
zend_function_entry tup_methods[] = {
    // 编解码接口
    PHP_ME(tup, encode, tup_encode_arginfo, ZEND_ACC_PUBLIC| ZEND_ACC_STATIC)
    PHP_ME(tup, decode, tup_decode_arginfo, ZEND_ACC_PUBLIC| ZEND_ACC_STATIC)

    // 这两个是给server用的,反向的编解码接口
    PHP_ME(tup, encodeRspPacket, tup_encode_rsp_packet_arginfo, ZEND_ACC_PUBLIC| ZEND_ACC_STATIC)
    // 这个接口未必需要啦,看情况
    PHP_ME(tup, decodeReqPacket, tup_decode_req_packet_arginfo, ZEND_ACC_PUBLIC| ZEND_ACC_STATIC)

    PHP_ME(tup, putStruct, tup_put_struct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getStruct, tup_get_struct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    PHP_ME(tup, putBool, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getBool, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putChar, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getChar, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putUInt8, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getUInt8, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putShort, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getShort, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putUInt16, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getUInt16, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putInt32, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getInt32, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putUInt32, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getUInt32, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putInt64, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getInt64, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putDouble, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getDouble, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putFloat, put_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getFloat, get_common_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putString, tup_put_string_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getString, tup_get_string_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putVector, tup_put_vector_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getVector, tup_get_vector_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, putMap, tup_put_map_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(tup, getMap, tup_get_map_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};
/* }}} */

/* {{{ ttup_module_entry
 */
zend_module_entry phptars_module_entry = {
    STANDARD_MODULE_HEADER_EX,
    NULL,
    NULL,
    "phptars",
    tup_methods,
    PHP_MINIT(phptars),
    PHP_MSHUTDOWN(phptars),
    NULL,
    NULL,
    PHP_MINFO(phptars),
    PHP_TARS_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHPTARS
ZEND_GET_MODULE(phptars)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(phptars)
{
    zend_class_entry ce;

    // tup
    INIT_CLASS_ENTRY(ce, "TUPAPI", tup_methods);
    tup_ce = zend_register_internal_class(&ce);

    // tup_exception
    INIT_CLASS_ENTRY(ce, "TARS_Exception", tup_exception_methods);
    tup_exception_ce = my_zend_register_internal_class_ex(&ce, zend_exception_get_default(), NULL);


    TUP_STARTUP(ttars);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(phptars)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(phptars)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "phptars support", "enabled");
    php_info_print_table_row(2, "phptars version", PHP_TARS_VERSION);
    php_info_print_table_end();

}
/* }}} */

/* {{{ tup_throw_exception(int err_code, char *fmt, ...)
 */
void tup_throw_exception(long err_code, char *fmt, ...) {

    va_list args;
    char *err_msg;

    va_start(args, fmt);
    vspprintf(&err_msg, 128, fmt, args);
    va_end(args);

    zend_throw_exception(tup_exception_ce, err_msg, err_code);
    efree(err_msg);
}
/* }}} */

PHP_METHOD(tup_exception, __construct) {
    char *msg;
    long code;
    size_t msg_len;
    zval *self;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STRING(msg, msg_len)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(code)
    ZEND_PARSE_PARAMETERS_END();

    self = getThis();
    zend_update_property_string(Z_OBJCE_P(self), Z_OBJ_P(self), ZEND_STRL("message"), msg);

    if (code) {
        zend_update_property_long(Z_OBJCE_P(self), Z_OBJ_P(self), ZEND_STRL("code"), code);
    }
}
/* }}} */

/* {{{ __tup_PUT
 */
#define __TUP_PUT(type, packer) do { \
    char *name, *buf; \
    int ret; \
    size_t name_len; \
    uint32_t len; \
    zval *value; \
    long iVersion=3; \
    type dest; \
    ZEND_PARSE_PARAMETERS_START(2, 3) \
        Z_PARAM_STRING(name, name_len) \
        Z_PARAM_ZVAL(value) \
        Z_PARAM_OPTIONAL \
        Z_PARAM_LONG(iVersion) \
    ZEND_PARSE_PARAMETERS_END(); \
    UniAttribute *att = UniAttribute_new(); \
    if (!att) {return MALLOC_EXCEPTION(#type);} \
    if(3 == iVersion) { \
        ret = packer ## _packer(value, NULL, 0, (void *)&dest); \
        if (ret != TARS_SUCCESS) {return CONVERT_EXCEPTION(ret, #type);}\
        ret = TUP_put ## type(att, name, dest); \
        if (ret != TARS_SUCCESS) { \
            UniAttribute_del(&att); \
            return PACK_EXCEPTION(ret, #type); \
        } \
    }\
    else { \
        int tag = atoi(name);\
        ret = packer ## _packer(value, NULL, tag, (void *)&dest); \
        if (ret != TARS_SUCCESS) {return CONVERT_EXCEPTION(ret, #type);}\
        ret = TarsOutputStream_write ## type(att->value_os, dest, tag); \
        if (ret != TARS_SUCCESS) { \
            UniAttribute_del(&att); \
            return PACK_EXCEPTION(ret, #type); \
        } \
    }\
    len = TarsOutputStream_getLength(att->value_os); \
    buf = TarsMalloc(len); \
    if(!buf) { \
        UniAttribute_del(&att); \
        RETURN_LONG(TARS_MALLOC_ERROR); \
    } \
    memcpy(buf, TarsOutputStream_getBuffer(att->value_os), TarsOutputStream_getLength(att->value_os)); \
    UniAttribute_del(&att); \
    MY_RETVAL_STRINGL(buf, len, 1); \
    TarsFree(buf); \
} while (0)
/* }}} */

/* {{{ __TUP_GET
 */
#define __TUP_GET(type, dest) do { \
    char *name, *buf; \
    long iVersion=3;\
    zend_bool is_require=0;\
    int ret; \
    size_t name_len, len; \
    ZEND_PARSE_PARAMETERS_START(2, 4) \
        Z_PARAM_STRING(name, name_len) \
        Z_PARAM_STRING(buf, len) \
        Z_PARAM_OPTIONAL \
        Z_PARAM_BOOL(is_require) \
        Z_PARAM_LONG(iVersion) \
    ZEND_PARSE_PARAMETERS_END(); \
    UniAttribute *att = UniAttribute_new(); \
    if (!att) {MALLOC_EXCEPTION(#type); return ;}\
    /* 解码 */ \
    if(3 == iVersion) { \
        TarsInputStream *is_string;\
        is_string = TarsInputStream_new();\
        if (!is_string){UniAttribute_del(&att); MALLOC_EXCEPTION(#type); return ;} \
        TarsInputStream_setBuffer(is_string, buf, len); \
        ret = TarsInputStream_readMap(is_string, att->m_data, 0, true); \
        if (TARS_SUCCESS != ret) {TarsInputStream_del(&is_string); UniAttribute_del(&att); READ_MAP_EXCEPTION(); return ;} \
        /* 解包 */ \
        ret = TUP_get ## type(att, name, dest, is_require); \
        if (ret != -6 && ret != TARS_SUCCESS) { \
            UNPACK_EXCEPTION(ret, #type); \
            UniAttribute_del(&att); \
            TarsInputStream_del(&is_string); \
            return ; \
        } \
        TarsInputStream_del(&is_string); \
    }\
    else { \
        int tag = atoi(name);\
        TarsInputStream_setBuffer(att->value_is, buf, len); \
        ret = TarsInputStream_read ## type(att->value_is, dest, tag, is_require); \
        if (ret != -6 && ret != TARS_SUCCESS) { \
            UNPACK_EXCEPTION(ret, #type); \
            UniAttribute_del(&att); \
            return ; \
        } \
    } \
    UniAttribute_del(&att); \
} while (0)
/* }}} */

/**
 * 通用编码函数
 */
PHP_METHOD(tup, encode) {
    char *servantName, *funcName;
    long iVersion, iRequestId, cPacketType, iMessageType, iTimeout;
    uint32_t outBuffLen;
    char *outBuff = NULL;
    size_t servantLen, funcLen;

    zval *inbuf_arr;
    zval *contexts;
    zval *statuses;
    int ret;

    ZEND_PARSE_PARAMETERS_START(10, 10)
        Z_PARAM_LONG(iVersion)
        Z_PARAM_LONG(iRequestId)
        Z_PARAM_STRING(servantName, servantLen)
        Z_PARAM_STRING(funcName, funcLen)
        Z_PARAM_LONG(cPacketType)
        Z_PARAM_LONG(iMessageType)
        Z_PARAM_LONG(iTimeout)
        Z_PARAM_ARRAY(contexts)
        Z_PARAM_ARRAY(statuses)
        Z_PARAM_ARRAY(inbuf_arr)
    ZEND_PARSE_PARAMETERS_END();

    /* 从buf数组中读出一个个的buffer，每个buffer就对应了输入的一个参数和它的值
    / 这是一个map的结构打成char之后的成果，tup_unipackert要做的事情就是把它放入正确的
    / sBuffer中 一个所谓的vector<char>
    */

    TarsOutputStream *os_map=NULL;

    os_map = TarsOutputStream_new();
    if (!os_map)
    {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }

    TarsOutputStream *os_tmp = TarsOutputStream_new();
    if (!os_tmp) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }

    // 遍历buf数组,顺序看起来没关系，太赞了。
    JMapWrapper *map_wrapper = JMapWrapper_new("string", "list<char>");

    if(iVersion == 3) {
        zend_string *zkey;
        zval *inbuf_iter;
        ulong num_key;

        char *key;

        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(inbuf_arr), num_key, zkey, inbuf_iter){

            key = ZSTR_VAL(zkey);

            // 针对每一个buf,现在已经获取了key->buf这样的一个键值对
            char *inbuf_val;
            uint32_t inbuf_len;
            convert_to_string(inbuf_iter);
            inbuf_val = Z_STRVAL_P(inbuf_iter);
            inbuf_len = Z_STRLEN_P(inbuf_iter);

            TarsOutputStream_reset(os_tmp);
            TarsOutputStream_reset(os_map);

            ret = TarsOutputStream_writeStringBuffer(os_tmp, key, strlen(key), 0);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = TarsOutputStream_writeVectorCharBuffer(os_map, inbuf_val, inbuf_len, 1);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = JMapWrapper_put(map_wrapper, TarsOutputStream_getBuffer(os_tmp), TarsOutputStream_getLength(os_tmp),
                                  TarsOutputStream_getBuffer(os_map), TarsOutputStream_getLength(os_map));
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

        }ZEND_HASH_FOREACH_END();

        TarsOutputStream_reset(os_tmp);

        TarsOutputStream_writeMap(os_tmp,map_wrapper,0);
    } 
    else if (iVersion == 1) {
        zend_string *zkey;
        zval *inbuf_iter;
        ulong num_key;

        char *key;

        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(inbuf_arr), num_key, zkey, inbuf_iter){

            key = ZSTR_VAL(zkey);

            // 针对每一个buf,现在已经获取了key->buf这样的一个键值对
            char *inbuf_val;
            uint32_t inbuf_len;
            convert_to_string(inbuf_iter);
            inbuf_val = Z_STRVAL_P(inbuf_iter);
            inbuf_len = Z_STRLEN_P(inbuf_iter);

            ret = JString_append(os_tmp->_buf, inbuf_val, inbuf_len);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

        }ZEND_HASH_FOREACH_END();
    }

    // 将mapwrapper进行uniattribute的encode使之成为符合需求的字符串
    // 设置tup包初始化参数
    UniPacket *pack = UniPacket_new();
    pack->iVersion = iVersion;
    pack->cPacketType = (char) cPacketType;
    pack->iMessageType  = iMessageType;
    pack->iRequestId = iRequestId;
    pack->iTimeout = iTimeout;

    TarsOutputStream *context_key_tmp = TarsOutputStream_new();
    if (!context_key_tmp) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }
    TarsOutputStream *context_value_tmp = TarsOutputStream_new();
    if (!context_value_tmp) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }
    // 如果设置了context
    if(NULL != contexts) {
        HashTable *contextsHt= Z_ARRVAL_P(contexts);

        zend_string *zkey;
        zval *contextsIter;
        ulong num_key;

        char *key;

        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(contexts), num_key, zkey, contextsIter) {
            if (!zkey) {
                continue;
            }

            key = ZSTR_VAL(zkey);

            char *contextVal;
            uint32_t contextLen;
            convert_to_string(contextsIter);
            contextVal = Z_STRVAL_P(contextsIter);
            contextLen = Z_STRLEN_P(contextsIter);

            ret = TarsOutputStream_writeStringBuffer(context_key_tmp, key, strlen(key), 0);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = TarsOutputStream_writeStringBuffer(context_value_tmp, contextVal, contextLen, 1);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = JMapWrapper_put(pack->context, TarsOutputStream_getBuffer(context_key_tmp), TarsOutputStream_getLength(context_key_tmp),
                                  TarsOutputStream_getBuffer(context_value_tmp), TarsOutputStream_getLength(context_value_tmp));
            if(ret) {
                TUP_SET_CONTEXT_EXCEPTION();
                goto do_clean;
            }

        } ZEND_HASH_FOREACH_END();
    }

    // 如果设置了status
    if(NULL != statuses) {
        TarsOutputStream_reset(context_key_tmp);
        TarsOutputStream_reset(context_value_tmp);

        zend_string *zkey;
        zval *statusesIter;
        ulong num_key;

        char *key;

        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(statuses), num_key, zkey, statusesIter) {

            key = ZSTR_VAL(zkey);

            char *statusVal;
            uint32_t statusLen;
            convert_to_string(statusesIter);
            statusVal = Z_STRVAL_P(statusesIter);
            statusLen = Z_STRLEN_P(statusesIter);

            ret = TarsOutputStream_writeStringBuffer(context_key_tmp, key, strlen(key), 0);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = TarsOutputStream_writeStringBuffer(context_value_tmp, statusVal, statusLen, 1);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = JMapWrapper_put(pack->status, TarsOutputStream_getBuffer(context_key_tmp), TarsOutputStream_getLength(context_key_tmp),
                                  TarsOutputStream_getBuffer(context_value_tmp), TarsOutputStream_getLength(context_value_tmp));

            if(ret) {
                TUP_SET_STATUS_EXCEPTION();
                goto do_clean;
            }

        } ZEND_HASH_FOREACH_END();
    }
    if (context_key_tmp)      TarsOutputStream_del(&context_key_tmp);
    if (context_value_tmp)      TarsOutputStream_del(&context_value_tmp);


    JString_assign(pack->sServantName, servantName, servantLen);
    if(funcLen == 0) funcLen = strlen(funcName);
    JString_assign(pack->sFuncName, funcName, funcLen);

    // 拷贝进入sBuffer
    ret = JString_assign(pack->sBuffer, TarsOutputStream_getBuffer(os_tmp), TarsOutputStream_getLength(os_tmp));
    if (TARS_SUCCESS != ret) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }


    TarsOutputStream_reset(os_tmp);

    ret = UniPacket_encode(pack, os_tmp);
    if (TARS_SUCCESS != ret)
    {
        ENCODE_EXCEPTION(ret);
        goto do_clean;
    }

    // 以网络序的方式处理包头
    int iHeaderLen = tars_htonl(sizeof(Int32) + TarsOutputStream_getLength(os_tmp));

    outBuffLen = sizeof(Int32) + TarsOutputStream_getLength(os_tmp);

    outBuff = TarsMalloc(outBuffLen);
    if (!outBuff)  goto do_clean;

    memcpy(outBuff, &iHeaderLen, sizeof(Int32));
    memcpy(outBuff + sizeof(Int32), TarsOutputStream_getBuffer(os_tmp), TarsOutputStream_getLength(os_tmp));

    MY_RETVAL_STRINGL(outBuff, outBuffLen, 1);
    free(outBuff);

do_clean:
    if(pack) UniPacket_del(&pack);
    if(os_tmp) TarsOutputStream_del(&os_tmp);
    if (map_wrapper) JMapWrapper_del(&map_wrapper);
    if (os_map)      TarsOutputStream_del(&os_map);
    if (context_key_tmp)      TarsOutputStream_del(&context_key_tmp);
    if (context_value_tmp)      TarsOutputStream_del(&context_value_tmp);
}

PHP_METHOD(tup,encodeRspPacket) {
    long iVersion,cPacketType,iMessageType, iRequestId, iRet;
    uint32_t outBuffLen;
    char *outBuff = NULL;
    char *sResultDesc;
    size_t sResultDescLen;

    zval *inbuf_arr;
    zval *statuses;
    int ret;

    ZEND_PARSE_PARAMETERS_START(8, 8)
        Z_PARAM_LONG(iVersion)
        Z_PARAM_LONG(cPacketType)
        Z_PARAM_LONG(iMessageType)
        Z_PARAM_LONG(iRequestId)
        Z_PARAM_LONG(iRet)
        Z_PARAM_STRING(sResultDesc, sResultDescLen)
        Z_PARAM_ARRAY(inbuf_arr)
        Z_PARAM_ARRAY(statuses)
    ZEND_PARSE_PARAMETERS_END();

    /* 从buf数组中读出一个个的buffer，每个buffer就对应了输入的一个参数和它的值
    / 这是一个map的结构打成char之后的成果，tup_unipackert要做的事情就是把它放入正确的
    / sBuffer中 一个所谓的vector<char>
    */

    TarsOutputStream *os_map=NULL;

    os_map = TarsOutputStream_new();
    if (!os_map)
    {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }

    TarsOutputStream *os_tmp = TarsOutputStream_new();
    if (!os_tmp) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }


    zend_string *zkey;
    zval *inbuf_iter;
    ulong num_key;

    char *key;

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(inbuf_arr), num_key, zkey, inbuf_iter){

        key = ZSTR_VAL(zkey);

        // 针对每一个buf,现在已经获取了key->buf这样的一个键值对
        char *inbuf_val;
        uint32_t inbuf_len;
        convert_to_string(inbuf_iter);
        inbuf_val = Z_STRVAL_P(inbuf_iter);
        inbuf_len = Z_STRLEN_P(inbuf_iter);

        ret = JString_append(os_tmp->_buf, inbuf_val, inbuf_len);
        if (ret) {
            ENCODE_BUF_EXCEPTION();
            goto do_clean;
        }

    }ZEND_HASH_FOREACH_END();

    // 设置tup包初始化参数
    ResponsePacket *rsp_pack = ResponsePacket_new();

    // 拷贝进入sBuffer
    ret = JString_assign(rsp_pack->sBuffer, TarsOutputStream_getBuffer(os_tmp), TarsOutputStream_getLength(os_tmp));
    if (TARS_SUCCESS != ret) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }

    rsp_pack->iVersion     = 1;
    rsp_pack->cPacketType  = cPacketType;
    rsp_pack->iMessageType = iMessageType;
    rsp_pack->iRequestId   = iRequestId;
    rsp_pack->iRet         = iRet;
    JString_assign(rsp_pack->sResultDesc, sResultDesc, sResultDescLen);

    TarsOutputStream *key_tmp = TarsOutputStream_new();
    if (!key_tmp) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }
    TarsOutputStream *value_tmp = TarsOutputStream_new();
    if (!value_tmp) {
        MALLOC_EXCEPTION("Encode");
        goto do_clean;
    }

    // 如果设置了status
    if(NULL != statuses) {
        TarsOutputStream_reset(key_tmp);
        TarsOutputStream_reset(value_tmp);

        zend_string *zkey;
        zval *statusesIter;
        ulong num_key;

        char *key;

        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(statuses), num_key, zkey, statusesIter) {

            key = ZSTR_VAL(zkey);

            char *statusVal;
            uint32_t statusLen;
            convert_to_string(statusesIter);
            statusVal = Z_STRVAL_P(statusesIter);
            statusLen = Z_STRLEN_P(statusesIter);

            ret = TarsOutputStream_writeStringBuffer(key_tmp, key, strlen(key), 0);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = TarsOutputStream_writeStringBuffer(value_tmp, statusVal, statusLen, 1);
            if (ret) {
                ENCODE_BUF_EXCEPTION();
                goto do_clean;
            }

            ret = JMapWrapper_put(rsp_pack->status, TarsOutputStream_getBuffer(key_tmp), TarsOutputStream_getLength(key_tmp),
                                  TarsOutputStream_getBuffer(value_tmp), TarsOutputStream_getLength(value_tmp));

            if(ret) {
                TUP_SET_STATUS_EXCEPTION();
                goto do_clean;
            }

        } ZEND_HASH_FOREACH_END();
    }
    if (key_tmp)      TarsOutputStream_del(&key_tmp);
    if (value_tmp)      TarsOutputStream_del(&value_tmp);

    TarsOutputStream_reset(os_tmp);

    ret = ResponsePacket_encode(rsp_pack, os_tmp);


    if(ret) {
        ENCODE_EXCEPTION(ret);
        goto do_clean;
    }
    // 以网络序的方式处理包头
    int iHeaderLen = tars_htonl(sizeof(Int32) + TarsOutputStream_getLength(os_tmp));

    outBuffLen = sizeof(Int32) + TarsOutputStream_getLength(os_tmp);

    outBuff = TarsMalloc(outBuffLen);
    if (!outBuff)  goto do_clean;


    memcpy(outBuff, &iHeaderLen, sizeof(Int32));
    memcpy(outBuff + sizeof(Int32), TarsOutputStream_getBuffer(os_tmp), TarsOutputStream_getLength(os_tmp));


    MY_RETVAL_STRINGL(outBuff, outBuffLen, 1);
    free(outBuff);

do_clean:
    if(rsp_pack) ResponsePacket_del(&rsp_pack);
    if(os_tmp) TarsOutputStream_del(&os_tmp);
    if(os_map)      TarsOutputStream_del(&os_map);
    if(key_tmp)      TarsOutputStream_del(&key_tmp);
    if(value_tmp)      TarsOutputStream_del(&value_tmp);

}


PHP_METHOD(tup,decode) {
    char *outBuff = NULL;

    char *respBuffer;
    size_t respBufferLen;
    int ret;
    zval *ret_val;
    long iVersion = 3;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STRING(respBuffer, respBufferLen)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    if(3 == iVersion) {
        UniPacket *unpack = UniPacket_new();

        UniPacket_decode(unpack, respBuffer, respBufferLen);

        // 获取返回码
        int status;

        JString *tmp;
        tmp = JString_new();

        array_init(return_value);
        ret = Unipacket_getStatus(unpack,tmp);

        status = atoi(JString_data(tmp));
        if(status != TARS_SUCCESS) {
            add_assoc_long(return_value,"status",status);
            add_assoc_long(return_value,"iRet",status);
            if(tmp) JString_del(&tmp);
            if(unpack) UniPacket_del(&unpack);
            return;
        }

        // 首先判断一下iVersion
        int iVersion;
        iVersion = unpack->iVersion;

        uint32_t len;

        TarsOutputStream *os = TarsOutputStream_new();
        if (!os) {
            MALLOC_EXCEPTION("Decode");
            if(os) TarsOutputStream_del(&os);
            if(unpack) UniPacket_del(&unpack);
            if(tmp) JString_del(&tmp);
            return;
        }

        TarsOutputStream_writeMap(os,((UniAttribute *)unpack)->m_data,0);

        len = TarsOutputStream_getLength(os);

        outBuff = TarsMalloc(len);
        memcpy(outBuff, TarsOutputStream_getBuffer(os), TarsOutputStream_getLength(os));


        my_add_assoc_stringl(return_value,"buf",outBuff, len, 1); //兼容老版本,新的就用sBuffer吧
        my_add_assoc_stringl(return_value,"sBuffer",outBuff, len, 1);

        add_assoc_long(return_value,"status",status); //兼容老版本
        add_assoc_long(return_value,"iRet",status);

        int iRequestId;
        iRequestId = unpack->iRequestId;
        add_assoc_long(return_value,"iRequestId",iRequestId);

        char *sServantName = NULL;
        sServantName = JString_data(unpack->sServantName);
        my_add_assoc_stringl(return_value,"sServantName",sServantName,strlen(sServantName), 1);

        char *sFuncName = NULL;
        sFuncName = JString_data(unpack->sFuncName);
        my_add_assoc_stringl(return_value,"sFuncName",sFuncName,strlen(sFuncName), 1);

        if(os) TarsOutputStream_del(&os);
        if(unpack) UniPacket_del(&unpack);
        if(outBuff) TarsFree(outBuff);
        if(tmp) JString_del(&tmp);

    }
    else {
        ResponsePacket *unpack = ResponsePacket_new();

        ResponsePacket_decode(unpack, respBuffer, respBufferLen);

        // 获取返回码
        array_init(return_value);
        int iRet;

        iRet = unpack->iRet;
        add_assoc_long(return_value,"iRet",iRet);

        char *sResultDesc = NULL;
        sResultDesc = JString_data(unpack->sResultDesc);
        my_add_assoc_stringl(return_value,"sResultDesc",sResultDesc,strlen(sResultDesc), 1);

        if(iRet != TARS_SUCCESS) {
            if(unpack) ResponsePacket_del(&unpack);
            return;
        }

        uint32_t len;

        TarsOutputStream *os = TarsOutputStream_new();
        if (!os) {
            MALLOC_EXCEPTION("Decode");
            if(unpack) ResponsePacket_del(&unpack);
            if(os) TarsOutputStream_del(&os);
            return;
        }

        TarsOutputStream_writeMap(os,((UniAttribute *)unpack)->m_data,0);

        len = JString_size(unpack->sBuffer);

        outBuff = TarsMalloc(len);
        memcpy(outBuff, JString_data(unpack->sBuffer), len);


        my_add_assoc_stringl(return_value,"sBuffer",outBuff, len, 1);

        int iRequestId;
        iRequestId = unpack->iRequestId;
        add_assoc_long(return_value,"iRequestId",iRequestId);

        short iVersion;
        iVersion = unpack->iVersion;
        add_assoc_long(return_value,"iVersion",iVersion);

        int iMessageType;
        iMessageType = unpack->iMessageType;
        add_assoc_long(return_value,"iMessageType",iMessageType);

        char cPacketType;
        cPacketType = unpack->cPacketType;
        add_assoc_long(return_value,"cPacketType",cPacketType);

        // todo statuses
        if(unpack) ResponsePacket_del(&unpack);
        if(os) TarsOutputStream_del(&os);
        if(outBuff) TarsFree(outBuff);
    }
    return;
}

PHP_METHOD(tup,decodeReqPacket) {

    char *outBuff = NULL;

    char *respBuffer;
    size_t respBufferLen;
    int ret;
    zval *ret_val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(respBuffer, respBufferLen)
    ZEND_PARSE_PARAMETERS_END();

    // requestPacket和UniPacket的结构完全一样,只是另一个别称
    UniPacket *unpack = UniPacket_new();

    UniPacket_decode(unpack, respBuffer, respBufferLen);

    // 首先判断一下iVersion
    int iVersion;
    iVersion = unpack->iVersion;

    uint32_t len;

    TarsOutputStream *os = TarsOutputStream_new();
    if (!os) {
        MALLOC_EXCEPTION("Decode");
        if(os) TarsOutputStream_del(&os);
        if(unpack) UniPacket_del(&unpack);
        return;
    }

    array_init(return_value);
    add_assoc_long(return_value,"iVersion",iVersion);
    int iRequestId;
    iRequestId = unpack->iRequestId;
    add_assoc_long(return_value,"iRequestId",iRequestId);

    char *sServantName = NULL;
    sServantName = JString_data(unpack->sServantName);
    my_add_assoc_stringl(return_value,"sServantName",sServantName,strlen(sServantName), 1);

    char *sFuncName = NULL;
    sFuncName = JString_data(unpack->sFuncName);
    my_add_assoc_stringl(return_value,"sFuncName",sFuncName,strlen(sFuncName), 1);

    if(3 == iVersion) {

        TarsOutputStream_writeMap(os,((UniAttribute *)unpack)->m_data,0);

        len = TarsOutputStream_getLength(os);

        outBuff = TarsMalloc(len);
        memcpy(outBuff, TarsOutputStream_getBuffer(os), TarsOutputStream_getLength(os));


        my_add_assoc_stringl(return_value,"sBuffer",outBuff, len, 1);

        if(outBuff) TarsFree(outBuff);

    }
    else {
        len = JString_size(unpack->sBuffer);

        outBuff = TarsMalloc(len);
        memcpy(outBuff, JString_data(unpack->sBuffer), len);
        my_add_assoc_stringl(return_value,"sBuffer",outBuff, len, 1);

        if(outBuff) TarsFree(outBuff);

    }


    if(os) TarsOutputStream_del(&os);
    if(unpack) UniPacket_del(&unpack);


    return;
}

/* {{{ Ttup::putBool(string $name, boolean $bool)
 */
PHP_METHOD(tup, putBool) {
    __TUP_PUT(Bool, bool);
}
/* }}} */

/* {{{ TTUP::getBool(string $name, string $buf)
 */
PHP_METHOD(tup, getBool) {
    Bool b = false;
    __TUP_GET(Bool, &b);
    RETURN_BOOL(b);
}
/* }}} */

/* {{{ TTUP::putChar(string $name, mixed $value)
 */
PHP_METHOD(tup, putChar) {
    __TUP_PUT(Char, char);
}
/* }}} */

/* {{{ TTUP::getChar(string $name, string $buf)
 */
PHP_METHOD(tup, getChar) {
    Char b = 0;
    __TUP_GET(Char, &b);
    MY_RETURN_STRINGL(&b, 1, 1);
}
/* }}} */

/* {{{ TTUP::putChar(string $name, mixed $value)
 */
PHP_METHOD(tup, putUInt8) {
    __TUP_PUT(UInt8, uint8);
}
/* }}} */

/* {{{ TTUP::getUInt8(string $name, string $buf)
 */
PHP_METHOD(tup, getUInt8) {
    UInt8 i = 0;
    __TUP_GET(UInt8, &i);
    RETURN_LONG(i);
}
/* }}} */

/* {{{ TTUP::putShort(string $name, mixed $value)
 */
PHP_METHOD(tup, putShort) {
    __TUP_PUT(Short, short);
}
/* }}} */

/* {{{ TTUP::getShort(string $name, string $buf)
 */
PHP_METHOD(tup, getShort) {
    Short i = 0;
    __TUP_GET(Short, &i);
    RETURN_LONG(i);
}
/* }}} */

/* {{{ TTUP::putUInt16(string $name, mixed $value)
 */
PHP_METHOD(tup, putUInt16) {
    __TUP_PUT(UInt16, uint16);
}
/* }}} */

/* {{{ TTUP::getUInt16(string $name, string $buf)
 */
PHP_METHOD(tup, getUInt16) {
    UInt16 i = 0;
    __TUP_GET(UInt16, &i);
    RETURN_LONG(i);
}
/* }}} */

/* {{{ TTUP::putInt32(string $name, mixed $value)
 */
PHP_METHOD(tup, putInt32) {
    __TUP_PUT(Int32, int32);
}
/* }}} */

/* {{{ TTUP::getInt32(string $name, string $buf)
 */
PHP_METHOD(tup, getInt32) {
    Int32 i = 0;
    __TUP_GET(Int32, &i);
    RETURN_LONG(i);
}
/* }}} */


/* {{{ TTUP::putUInt32(string $name, mixed $value)
 */
PHP_METHOD(tup, putUInt32) {
    __TUP_PUT(UInt32, uint32);
}
/* }}} */

/* {{{ __TUP_GET_BIG_INT
 */
#if __WORDSIZE == 64 || defined(__x86_64) || defined(__x86_64__)
#define __TUP_GET_BIG_INT(type) \
    type i = 0; \
    __TUP_GET(type, &i); \
    RETURN_LONG(i);
#else
#define __TUP_GET_BIG_INT(type) \
    type i = 0; \
    __TUP_GET(type, &i); \
    if (i >= LONG_MIN && i <= LONG_MAX) { \
        RETURN_LONG(i);
    } else { \
        char  ll[32]; \
        int len; \
        len = slprintf(ll, 32, "%lld", i); \
        MY_RETURN_STRINGL(ll, len, 1); \
    }
#endif
/* }}} */

/* {{{ TTUP::getInt32(string $name, string $buf)
 */
PHP_METHOD(tup, getUInt32) {
    __TUP_GET_BIG_INT(UInt32)
}
/* }}} */

/* {{{ TTUP::putInt64(string $name, mixed $value)
 */
PHP_METHOD(tup, putInt64) {
    __TUP_PUT(Int64, int64);
}
/* }}} */

/* {{{ TTUP::getInt32(string $name, string $buf)
 */
PHP_METHOD(tup, getInt64) {
    __TUP_GET_BIG_INT(Int64)
}
/* }}} */

/* {{{ TTUP::putDouble(string $name, mixed $value)
 */
PHP_METHOD(tup, putDouble) {
    __TUP_PUT(Double, double);
}
/* }}} */

/* {{{ TTUP::getDouble(string $name, string $buf)
 */
PHP_METHOD(tup, getDouble) {
    Double i = 0;
    __TUP_GET(Double, &i);
    RETURN_DOUBLE(i);
}
/* }}} */

/* {{{ TTUP::putFloat(string $name, mixed $value)
 */
PHP_METHOD(tup, putFloat) {
    __TUP_PUT(Float, float);
}
/* }}} */

/* {{{ TTUP::getFloat(string $name, string $buf)
 */
PHP_METHOD(tup, getFloat) {
    Float i = 0;
    __TUP_GET(Float, &i);
    RETURN_DOUBLE(i);
}
/* }}} */

/* {{{ TTUP::putString(string $name, mixed $value)
 */
PHP_METHOD(tup, putString) {
    char *name, *buf;
    int ret;
    size_t name_len;
    uint32_t len;
    zval *value;
    JString *js = NULL;
    UniAttribute *att = NULL;
    long iVersion=3;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_ZVAL(value)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    js = JString_new();
    if (!js) {MALLOC_EXCEPTION("String"); return;}

    att = UniAttribute_new();
    if (!att) {
        MALLOC_EXCEPTION("String");
        goto do_clean;
    }

    if (3 == iVersion) {
        ret = string_packer(value, NULL, 0, NULL);
        if (ret != TARS_SUCCESS) {
            CONVERT_EXCEPTION(ret, "String");
            goto do_clean;
        }

        ret = JString_assign(js, Z_STRVAL_P(value), Z_STRLEN_P(value));
        if (ret != TARS_SUCCESS) {
            MALLOC_EXCEPTION("String");
            goto do_clean;
        }

        ret = TUP_putString(att, name, js);
        if (ret != TARS_SUCCESS) {
            PACK_EXCEPTION(ret, "String");
            goto do_clean;
        }
    } 
    else {
        int tag = atoi(name);
        ret = string_packer(value, att->value_os, tag, NULL);
        if (ret != TARS_SUCCESS) {
            CONVERT_EXCEPTION(ret, "String");
            goto do_clean;
        }
    }

    // 这次不需要再encode了
    len = TarsOutputStream_getLength(att->value_os);

    buf = TarsMalloc(len);

    if(NULL == buf) {
        MALLOC_EXCEPTION("String");
        goto do_clean;
    }

    memcpy(buf, TarsOutputStream_getBuffer(att->value_os), TarsOutputStream_getLength(att->value_os));

    MY_RETVAL_STRINGL(buf, len, 1);

do_clean :
    if (js) JString_del(&js);
    if (att) UniAttribute_del(&att);
    if (buf) TarsFree(buf);
}
/* }}} */

/* {{{ TTUP::getString(string $name, string $buf)
 */
PHP_METHOD(tup, getString) {

    char *name, *buf;
    size_t name_len, len;
    int ret;
    zend_bool is_require=0;
    JString *js = NULL;
    UniAttribute *att = NULL;
    long iVersion=3;

    ZEND_PARSE_PARAMETERS_START(2, 4)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_STRING(buf, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_BOOL(is_require)
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    att = UniAttribute_new();
    if (!att) {
        MALLOC_EXCEPTION("String");
        return ;
    }

    TarsInputStream *is_string;
    is_string = TarsInputStream_new();
    if (!is_string)
    {
        MALLOC_EXCEPTION("String");
        goto do_clean;
    }

    TarsInputStream_setBuffer(is_string, buf, len);

    js = JString_new();

    if (3 == iVersion) {
        ret = TarsInputStream_readMap(is_string, att->m_data, 0, false);
        if (ret == TARS_DECODE_EOPNEXT) {
            if (js) JString_del(&js);
            if (att) UniAttribute_del(&att);
            if(is_string) TarsInputStream_del(&is_string);
            RETVAL_EMPTY_STRING();
            return;
        }
        if (TARS_SUCCESS != ret) {
            MALLOC_EXCEPTION("String");
            goto do_clean;
        }

        ret = TUP_getString(att, name, js, is_require);
        if (ret == TARS_DECODE_EOPNEXT) {
            if (js) JString_del(&js);
            if (att) UniAttribute_del(&att);
            if(is_string) TarsInputStream_del(&is_string);
            RETVAL_EMPTY_STRING();
            return;
        }
        if (TARS_SUCCESS != ret) {
            MALLOC_EXCEPTION("String");
            goto do_clean;
        }
    } 
    else {
        int tag = atoi(name);
        ret = TarsInputStream_readString(is_string, js, tag, is_require);
        if (ret == TARS_DECODE_EOPNEXT) {
            if (js) JString_del(&js);
            if (att) UniAttribute_del(&att);
            if(is_string) TarsInputStream_del(&is_string);
            RETVAL_EMPTY_STRING();
            return;
        }
        if (ret != TARS_SUCCESS) {
            UNPACK_EXCEPTION(ret, "String");
            goto do_clean;
        }
    }

    MY_RETVAL_STRINGL(JS_STRVAL(js), JS_STRLEN(js), 1);

do_clean :
    if (js) JString_del(&js);
    if (att) UniAttribute_del(&att);
    if(is_string) TarsInputStream_del(&is_string);
}
/* }}} */

/* {{{ TUP::putVector
 */
PHP_METHOD(tup, putVector) {

    zval *clazz;
    char *name, *buf = NULL;
    size_t name_len;
    int ret;
    uint32_t len;
    JArray *vct = NULL;
    JString *js = NULL;
    long iVersion = 3;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_OBJECT_OF_CLASS(clazz, tars_vector_ce)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    vector_wrapper *obj = Z_VECTOR_WRAPPER_P(clazz);
    if (!IS_VALID_TYPE(obj->t)) return TYPE_EXCEPTOIN();

    if (IS_JSTRING(obj->t)) {
        js = obj->ctx->str;
    } else {
        vct = obj->ctx->vct;
    }

    UniAttribute *att = UniAttribute_new();
    if (!att) {
        MALLOC_EXCEPTION("Vector");
        return;
    }

    // 对于tup的编码,tag为默认的0,主要在encode的时候用name来进行编码
    int cur_tag = 0;
    if(1 == iVersion) {
        cur_tag = atoi(name);
    }

    if (IS_JSTRING(obj->t)) {
        ret = TarsOutputStream_writeVectorCharBuffer(att->value_os, JString_data(js), JString_size(js), cur_tag);
    } else {
        ret = TarsOutputStream_writeVector(att->value_os, vct, cur_tag);
    }

    if (ret != TARS_SUCCESS) {
        PACK_EXCEPTION(ret, "Vector");
        goto do_clean;
    }

    // 这次不需要再encode了
    len = TarsOutputStream_getLength(att->value_os);

    buf = TarsMalloc(len);

    if(NULL == buf) {
        MALLOC_EXCEPTION("Vector");
        goto do_clean;
    }

    memcpy(buf, TarsOutputStream_getBuffer(att->value_os), TarsOutputStream_getLength(att->value_os));

    MY_RETVAL_STRINGL(buf, len, 1);

do_clean :
    if (att) UniAttribute_del(&att);
    if (buf) TarsFree(buf);
    //if (js) JString_del(&js);
}
/* }}} */

/* {{{ TUP::getVector
 */
PHP_METHOD(tup, getVector) {

    char *buf, *name;
    size_t len, name_len;
    int ret;
    zval *clazz, *ret_val = NULL;
    JArray *vct;
    JString *js;
    zend_bool is_require = 0;
    long iVersion = 3;

    ZEND_PARSE_PARAMETERS_START(3, 5)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_OBJECT_OF_CLASS(clazz, tars_vector_ce)
        Z_PARAM_STRING(buf, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_BOOL(is_require)
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    vector_wrapper *obj = Z_VECTOR_WRAPPER_P(clazz);
    if (!IS_VALID_TYPE(obj->t)) return TYPE_EXCEPTOIN();

    UniAttribute *att = UniAttribute_new();
    if (!att) {
        MALLOC_EXCEPTION("Vector");
        goto do_clean;
    }

    TarsInputStream *is_string;
    is_string = TarsInputStream_new();

    if (!is_string)
    {
        MALLOC_EXCEPTION("Vector");
        goto do_clean;
    }

    TarsInputStream_setBuffer(is_string, buf, len);

    if (3 == iVersion) {
        ret = TarsInputStream_readMap(is_string, att->m_data, 0, false);
        if (ret == TARS_DECODE_EOPNEXT) {
            if (att) UniAttribute_del(&att);
            if(is_string) TarsInputStream_del(&is_string);
            array_init(return_value);
            return;
        }
        if (TARS_SUCCESS != ret) {
            MALLOC_EXCEPTION("Vector");
            goto do_clean;
        }

        // 区分vector的类型
        if (IS_JSTRING(obj->t)) {
            js = obj->ctx->str;
            JString_clear(js);
            ret = TUP_getVectorChar(att, name, js, is_require);
            if (ret == TARS_DECODE_EOPNEXT) {
                if (att) UniAttribute_del(&att);
                if(is_string) TarsInputStream_del(&is_string);
                array_init(return_value);
                return;
            }
            if (ret != TARS_SUCCESS) {
                UNPACK_EXCEPTION(ret, "Vector");
                goto do_clean;
            }

            MY_RETVAL_STRINGL(JS_STRVAL(js), JS_STRLEN(js), 1);
            return;
        } else {

            vct = obj->ctx->vct;
            JArray_clear(vct);
            ret = TUP_getVector(att, name, vct, is_require);
            if (ret == TARS_DECODE_EOPNEXT) {
                if (att) UniAttribute_del(&att);
                if(is_string) TarsInputStream_del(&is_string);
                array_init(return_value);
                return;
            }

            if (ret != TARS_SUCCESS) {
                UNPACK_EXCEPTION(ret, "Vector");
                goto do_clean;
            }

            // 解包成PHP数据结构
            ALLOC_INIT_ZVAL(ret_val);
            ret = vector_unpacker(NULL, 0, is_require, clazz, (void **)&ret_val);
            if (ret == TARS_DECODE_EOPNEXT) {
                if (att) UniAttribute_del(&att);
                if(is_string) TarsInputStream_del(&is_string);
                array_init(return_value);
                return;
            }
            if (ret != TARS_SUCCESS) {
                UNPACK_EXCEPTION(ret, "Vector");
                goto do_clean;
            }
        }
    } 
    else {
        int cur_tag = atoi(name);

        // 区分vector的类型
        if (IS_JSTRING(obj->t)) {
            js = obj->ctx->str;
            JString_clear(js);
            ret = TarsInputStream_readVectorChar(is_string, js, cur_tag, is_require);
            if (ret == TARS_DECODE_EOPNEXT) {
                if (att) UniAttribute_del(&att);
                if(is_string) TarsInputStream_del(&is_string);
                array_init(return_value);
                return;
            }

            if (ret != TARS_SUCCESS) {
                UNPACK_EXCEPTION(ret, "Vector");
                goto do_clean;
            }

            MY_RETVAL_STRINGL(JS_STRVAL(js), JS_STRLEN(js), 1);
            return;
        } else {
            vct = obj->ctx->vct;
            JArray_clear(vct);

            ret = TarsInputStream_readVector(is_string, vct, cur_tag, is_require);
            if (ret == TARS_DECODE_EOPNEXT) {
                if (att) UniAttribute_del(&att);
                if(is_string) TarsInputStream_del(&is_string);
                array_init(return_value);
                return;
            }
            if (ret != TARS_SUCCESS) {
                UNPACK_EXCEPTION(ret, "Vector");
                goto do_clean;
            }
            // 解包成PHP数据结构
            ALLOC_INIT_ZVAL(ret_val);
            ret = vector_unpacker(NULL, 0, is_require, clazz, (void **)&ret_val);
            if (ret == TARS_DECODE_EOPNEXT) {
                if (att) UniAttribute_del(&att);
                if(is_string) TarsInputStream_del(&is_string);
                array_init(return_value);
                return;
            }
            if (ret != TARS_SUCCESS) {
                UNPACK_EXCEPTION(ret, "Vector");
                goto do_clean;
            }
        }
    }

    RETVAL_ZVAL(ret_val, 1, 1);

do_clean :
    if (att) UniAttribute_del(&att);
    if(is_string) TarsInputStream_del(&is_string);
}
/* }}} */

/* {{{ TTUP::putMap
 */
PHP_METHOD(tup, putMap) {
    zval *clazz;
    char *name, *buf = NULL;
    int ret;
    size_t name_len;
    uint32_t len;
    JMapWrapper *container;
    long iVersion=3;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_OBJECT_OF_CLASS(clazz, tars_map_ce)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    map_wrapper *obj = Z_MAP_WRAPPER_P(clazz);
    container = obj->ctx;

    UniAttribute *att = UniAttribute_new();
    if (!att) return MALLOC_EXCEPTION("Map");

    if (3 == iVersion) {
        ret = TUP_putMap(att, name, container);
        if (ret != TARS_SUCCESS) {
            PACK_EXCEPTION(ret, "Map");
            goto do_clean;
        }
    } else {
        int tag = atoi(name);
        ret = map_packer(NULL, att->value_os, tag, clazz);
        if (ret != TARS_SUCCESS) {
            PACK_EXCEPTION(ret, "Map");
            goto do_clean;
        }
    }

    len = TarsOutputStream_getLength(att->value_os);
    buf = TarsMalloc(len);

    if(NULL == buf) {
        MALLOC_EXCEPTION("Map");
        goto do_clean;
    }

    memcpy(buf, TarsOutputStream_getBuffer(att->value_os), TarsOutputStream_getLength(att->value_os));

    MY_RETVAL_STRINGL(buf, len, 1);
do_clean :
    UniAttribute_del(&att);
    if (buf) TarsFree(buf);
}
/* }}} */

/* {{{ TTUP::getMap(stirng $name, TTARS_Map $map)
 */
PHP_METHOD(tup, getMap) {

    zval *clazz, *ret_val = NULL;
    char *buf, *name;
    size_t len, name_len;
    int ret = 0;
    JMapWrapper *container;
    UniAttribute *att = NULL;
    zend_bool is_require = 0;
    long iVersion = 3;

    ZEND_PARSE_PARAMETERS_START(3, 5)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_OBJECT_OF_CLASS(clazz, tars_map_ce)
        Z_PARAM_STRING(buf, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_BOOL(is_require)
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    att = UniAttribute_new();
    if (!att) {ret = TARS_MALLOC_ERROR; goto do_clean; }

    TarsInputStream *is_string;
    is_string = TarsInputStream_new();
    if (!is_string)
    {
        MALLOC_EXCEPTION("Map");
        goto do_clean;
    }

    TarsInputStream_setBuffer(is_string, buf, len);

    if (3 == iVersion) {
        ret = TarsInputStream_readMap(is_string, att->m_data, 0, false);
        if (ret == TARS_DECODE_EOPNEXT) {
            UniAttribute_del(&att);
            if(NULL != is_string) TarsInputStream_del(&is_string);
            array_init(return_value);
            return;
        }
        if (TARS_SUCCESS != ret) {
            DECODE_EXCEPTION(ret);
            goto do_clean;
        }

        map_wrapper *obj = Z_MAP_WRAPPER_P(clazz);
        container = obj->ctx;
        JMapWrapper_clear(container);

        ret = TUP_getMap(att, name, container, is_require);
        if (ret == TARS_DECODE_EOPNEXT) {
            UniAttribute_del(&att);
            if(NULL != is_string) TarsInputStream_del(&is_string);
            array_init(return_value);
            return;
        }
        if (ret != TARS_SUCCESS) {
            DECODE_EXCEPTION(ret);
            goto do_clean;
        }

        ALLOC_INIT_ZVAL(ret_val);
        ret = _map_to_array(clazz, container, (void **)&ret_val);
        if (ret != TARS_SUCCESS) {
            UNPACK_EXCEPTION(ret, "Map");
            goto do_clean;
        }

    } 
    else {
        int tag = atoi(name);
        ALLOC_INIT_ZVAL(ret_val);
        ret = map_unpacker(is_string, tag, is_require, clazz,(void **)&ret_val);
        if (ret == TARS_DECODE_EOPNEXT) {
            UniAttribute_del(&att);
            if(NULL != is_string) TarsInputStream_del(&is_string);
            array_init(return_value);
            return;
        }
        if (TARS_SUCCESS != ret) {
            UNPACK_EXCEPTION(ret, "Map");
            goto do_clean;
        }
    }

    RETVAL_ZVAL(ret_val, 1, 1);

do_clean :
    UniAttribute_del(&att);
    if(NULL != is_string) TarsInputStream_del(&is_string);

}
/* }}} */

PHP_METHOD(tup, putStruct) {
    zval *clazz;
    char *name, *buf = NULL;
    int ret;
    size_t name_len;
    uint32_t len;
    UniAttribute *att = NULL;
    long iVersion = 3;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_OBJECT_OF_CLASS(clazz, tars_struct_ce)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    att = UniAttribute_new();
    if (!att)  return MALLOC_EXCEPTION("Struct");

    if (3 == iVersion) {
        ret = struct_packer(NULL, att->value_os, 0, (zval *)clazz);
        if (ret != TARS_SUCCESS) {
            PACK_EXCEPTION(ret, name);
            goto do_clean;
        }
    } 
    else {
        int tag = atoi(name);

        ret = struct_packer(NULL,att->value_os, tag, clazz);

        if (ret != TARS_SUCCESS) {
            PACK_EXCEPTION(ret, name);
            goto do_clean;
        }
    }

    len = TarsOutputStream_getLength(att->value_os);

    buf = TarsMalloc(len);

    if(NULL == buf) {
        MALLOC_EXCEPTION("Struct");
        goto do_clean;
    }

    memcpy(buf, TarsOutputStream_getBuffer(att->value_os), TarsOutputStream_getLength(att->value_os));

    MY_RETVAL_STRINGL(buf, len, 1);

do_clean :
    UniAttribute_del(&att);
    if (buf) TarsFree(buf);
}
/* }}} */


/* {{{ TTUP::getStruct(string $name, string $buf, TTARS_Struct $struct)
+ */
PHP_METHOD(tup, getStruct) {

    char *buf, *name;
    size_t len, name_len;
    int ret;
    zval *clazz, *ret_val = NULL;
    UniAttribute *attr = NULL;
    zend_bool is_require = 0;
    long iVersion=3;

    ZEND_PARSE_PARAMETERS_START(3, 5)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_OBJECT_OF_CLASS(clazz, tars_struct_ce)
        Z_PARAM_STRING(buf, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_BOOL(is_require)
        Z_PARAM_LONG(iVersion)
    ZEND_PARSE_PARAMETERS_END();

    // 解码
    attr = UniAttribute_new();
    TarsInputStream *is_string;
    is_string = TarsInputStream_new();

    if (!is_string)
    {
        MALLOC_EXCEPTION("Struct");
        goto do_clean;
    }

    TarsInputStream_setBuffer(is_string, buf, len);

    if (3 == iVersion) {
        ret = TarsInputStream_readMap(is_string, attr->m_data, 0, true);
        if (TARS_SUCCESS != ret) {
            READ_MAP_EXCEPTION();
            goto do_clean;
        }
        // todo 中间函数的替换。
        ALLOC_INIT_ZVAL(ret_val);
        ret = php_TUP_getStruct(attr, name, clazz,(void **)&ret_val, is_require);
        if(TARS_DECODE_EOPNEXT == ret) {
            if(NULL != is_string) TarsInputStream_del(&is_string);
            if(NULL != attr) UniAttribute_del(&attr);
            array_init(return_value);
            return;
        }
        if (TARS_SUCCESS != ret) {
            UNPACK_EXCEPTION(ret, name);
            goto do_clean;
        }
    }
    else {
        int tag = atoi(name);
        ALLOC_INIT_ZVAL(ret_val);
        ret = struct_unpacker(is_string, tag, is_require, clazz,(void **)&ret_val);

        if(TARS_DECODE_EOPNEXT == ret) {
            if(NULL != is_string) TarsInputStream_del(&is_string);
            if(NULL != attr) UniAttribute_del(&attr);
            array_init(return_value);
            return;
        }

        if (TARS_SUCCESS != ret) {
            UNPACK_EXCEPTION(ret, name);
            goto do_clean;
        }
    }

    RETVAL_ZVAL(ret_val, 1, 1);

do_clean :
    if(NULL != is_string) TarsInputStream_del(&is_string);
    if(NULL != attr) UniAttribute_del(&attr);
}




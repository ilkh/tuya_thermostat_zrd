#include "tl_common.h"

#include "app_main.h"

static const char8_t *tuya_manuf_name1[] = {
                                           "u9bfwha0",
                                           "aoclfnxz",
//                                           "ztvwu4nk",
//                                           "5toc8efa",
//                                           "ye5jkfsb",
                                            NULL};

static const char8_t *tuya_manuf_name2[] = {
                                           "edl8pz1k",
                                            NULL};

static const char8_t *tuya_manuf_name3[] = {
                                           "tagezcph",
                                            NULL};

static const char8_t *tuya_manuf_name4[] = {
                                           "xyugziqv",
                                            NULL};

const char8_t **tuya_manuf_names[] = {
                                      tuya_manuf_name1,
                                      tuya_manuf_name2,
                                      tuya_manuf_name3,
                                      tuya_manuf_name4
};

uint8_t manuf_name = MANUF_NAME_1;

data_point_st_t *data_point_model_arr[DP_IDX_MAXNUM] = {
                                                        data_point_model1,
                                                        data_point_model2,
                                                        data_point_model3,
                                                        data_point_model4
};

// Not worked in gcc 4.5.1
//data_point_st_t *data_point_model = data_point_model_arr[MANUF_NAME_1];
data_point_st_t *data_point_model = data_point_model1;

void data_point_model_init() {

    data_point_model = data_point_model_arr[MANUF_NAME_1];

//    for(uint16_t i = 0; i < DP_IDX_MAXNUM; i++) {
//        printf("i: %d, id: 0x%x, type: %d, len: %d, divisor: %d\r\n",
//                i, data_point_model[i].id, data_point_model[i].type, data_point_model[i].len, data_point_model[i].divisor);
//    }
}

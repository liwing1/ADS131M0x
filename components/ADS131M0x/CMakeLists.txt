set(component_srcs)

idf_component_register(SRCS "ads131m0x.c" "hal.c" "${component_srcs}"
                       PRIV_REQUIRES driver
                       INCLUDE_DIRS ".")

# 将库文件源文件添加到库
add_library(my_library SHARED  zip_wdm/zip_api_wdm.cpp)

# 设置共享库的版本信息
set_target_properties(my_library PROPERTIES
    VERSION 1.0
    SOVERSION 1
)
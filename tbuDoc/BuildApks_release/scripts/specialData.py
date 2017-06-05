class specialData:
    __channel_id=''
    __zhang_qd =''
    __uuc_own_channel =''
    __package_name=''
    __letu_key=''
#     def __init__(self,channel_id,package_name,letu_key):
#         self.__channel_id=channel_id
#         self.__package_name=package_name
#         self.__letu_key=letu_key
    def set_channel_id(self,channel_id):
        self.__channel_id=channel_id
    def set_package_name(self,package_name):
        self.__package_name=package_name
    def set_letu_key(self,letu_key):
        self.__letu_key=letu_key
    def set_zhang_qd(self,zhang_qd):
        self.__zhang_qd =zhang_qd
    def set_uuc_own_channel(self,uuc_own_channel):
        self.__uuc_own_channel=uuc_own_channel
        
    def get_channel_id(self):
        return self.__channel_id
    def get_package_name(self):
        return self.__package_name
    def get_letu_key(self):
        return self.__letu_key
    def get_zhang_qd(self):
        return self.__zhang_qd
    def get_uuc_own_channel(self):
        return self.__uuc_own_channel

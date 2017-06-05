# -*- coding: UTF-8 -*-

import sys
reload(sys)
sys.setdefaultencoding("utf-8")


class configData:
    __client_order_id = ''

    # paths
    __b_up_path = ''      # B工程的上层目录
    __project_path = ''   # 主工程的当前目录
    __dst_path = ''       # B工程和主工程的副本目录
    __save_path = ''       # 最终apks所在目录
    __config_files_path = ''  # configfiles文件夹所在的目录
    __other_libraries = []

    # gameinfo
    __output_name = ''
    __game_show_version = ''
    __game_version = ''
#     __package_name=''
    __screen_orientation = ''
    __show_app_name = ''
    __tbu_id = ''
    __px_ad = ''
    __yt_ad = ''
    __ox_ad = ''
    __plugin_lists = ''
    __plugin_lists_phone = ''
    __PAY_SEQ_CU = ''
    __PAY_SEQ_CT = ''
    __PAY_SEQ_CM = ''
    __PAY_SEQ_DEFAULT = ''

    # poxiao
    __poxiao_game_id = ''

    # zhimeng
    __zhimeng_app_id = ''
    __zhimeng_merchant_id = ''
    __zhimeng_merchant_passwd = ''

    # letu
    __letu_app_id = ''
    __letu_merchant_id = ''
    __letu_merchant_key = ''

    #zhang
    __zhang_app_id =''
    __zhang_key=''
    __zhang_channel_id=''

     #uuc
    __uuc_app_id = ''
    __uuc_merchant_key =''
    __uuc_secret_key=''

    #wechat
    __wechat_app_id = ''
    __wechat_merchant_id = ''

    # avos
    __avos_app_id = ''
    __avos_app_key = ''
    __special_data = []

    def set_by_dict(self, **dict):
        '''
                        若要通过字典初始化所有成员变量，则dict中的key应和该类中的成员变量名对应
        '''
        self.__client_order_id = dict['client_order_id']
        self.__b_up_path = dict['b_up_path']
        self.__project_path = dict['project_path']
        self.__dst_path = dict['dst_path']
        self.__config_files_path = dict['config_files_path']
        self.__other_libraries = dict['other_libraries']
        self.__output_name = dict['output_name']
        self.__game_show_version = dict['game_show_version']
        self.__game_version = dict['game_version']
#         self.__package_name=dict['package_name']
        self.__show_app_name = dict['show_app_name']
        self.__screen_orientation = dict['screen_orientation']
        self.__avos_app_id = dict['avos_app_id']
        self.__avos_app_key = dict['avos_app_key']

        self.__tbu_id = dict['tbu_id']
        if dict.has_key('poxiao_game_id'):
            self.__poxiao_game_id = dict['poxiao_game_id']
        if dict.has_key('zhimeng_app_id'):
            self.__zhimeng_app_id = dict['zhimeng_app_id']
            self.__zhimeng_merchant_id = dict['zhimeng_merchant_id']
            self.__zhimeng_merchant_passwd = dict['zhimeng_merchant_passwd']
        if dict.has_key('letu_app_id'):
            self.__letu_app_id = dict['letu_app_id']
            self.__letu_merchant_id = dict['letu_merchant_id']
            self.__letu_merchant_key = dict['letu_merchant_key']
        if dict.has_key('zhang_app_id'):
            self.__zhang_app_id = dict['zhang_app_id']
            self.__zhang_key = dict['zhang_key']
            self.__zhang_channel_id = dict['zhang_channel_id']
        if dict.has_key('uuc_app_id'):
            print "------------------------has_key uuc_app_id"
            self.__uuc_app_id = dict['uuc_app_id']
            self.__uuc_merchant_key = dict['uuc_merchant_key']
            self.__uuc_secret_key = dict['uuc_secret_key']
        if dict.has_key('wechat_app_id'):
            self.__wechat_app_id = dict['wechat_app_id']
            self.__wechat_merchant_id = dict['wechat_merchant_id']
       

        self.__special_data = dict['special_data']
        self.__px_ad = dict['px_ad']
        self.__yt_ad = dict['yt_ad']
        self.__ox_ad = dict['ox_ad']
        self.__plugin_lists_phone = dict['plugin_lists_phone']

        self.__plugin_lists = dict['plugin_lists']
        self.__PAY_SEQ_CU = dict['PAY_SEQ_CU']
        self.__PAY_SEQ_CT = dict['PAY_SEQ_CT']
        self.__PAY_SEQ_CM = dict['PAY_SEQ_CM']
        self.__PAY_SEQ_DEFAULT = dict['PAY_SEQ_DEFAULT']

        self.__save_path = dict['save_path']

    def get_other_libraries(self):
        return self.__other_libraries

    def get_PAY_SEQ_CU(self):
        return self.__PAY_SEQ_CU

    def get_PAY_SEQ_CT(self):
        return self.__PAY_SEQ_CT

    def get_PAY_SEQ_CM(self):
        return self.__PAY_SEQ_CM

    def get_PAY_SEQ_DEFAULT(self):
        return self.__PAY_SEQ_DEFAULT

    def get_config_files_path(self):
        return self.__config_files_path

    def get_client_order_id(self):
        return self.__client_order_id

    def get_plugin_lists(self):
        return self.__plugin_lists

    def get_save_path(self):
        return self.__save_path

    def get_px_ad(self):
        return self.__px_ad

    def get_yt_ad(self):
        return self.__yt_ad

    def get_ox_ad(self):
        return self.__ox_ad

    def get_b_up_path(self):
        return self.__b_up_path

    def get_project_path(self):
        return self.__project_path

    def get_dst_path(self):
        return self.__dst_path

    def get_output_name(self):
        return self.__output_name

    def get_game_show_version(self):
        return self.__game_show_version

    def get_game_version(self):
        return self.__game_version

#     def get_package_name(self):
#         return self.__package_name

    def get_screen_orientation(self):
        return self.__screen_orientation

    def get_avos_app_id(self):
        return self.__avos_app_id

    def get_avos_app_key(self):
        return self.__avos_app_key

    def get_show_app_name(self):
        return self.__show_app_name

    def get_tbu_id(self):
        return self.__tbu_id

    def get_poxiao_game_id(self):
        return self.__poxiao_game_id

    def get_zhimeng_app_id(self):
        return self.__zhimeng_app_id

    def get_zhimeng_merchant_id(self):
        return self.__zhimeng_merchant_id

    def get_zhimeng_merchant_passwd(self):
        return self.__zhimeng_merchant_passwd

    def get_letu_app_id(self):
        return self.__letu_app_id

    def get_letu_merchant_id(self):
        return self.__letu_merchant_id

    def get_letu_merchant_key(self):
        return self.__letu_merchant_key

    def get_zhang_app_id(self):
        return self.__zhang_app_id

    def get_zhang_key(self):
        return self.__zhang_key

    def get_zhang_channel_id(self):
        return self.__zhang_channel_id


    def get_uuc_app_id(self):
        return self.__uuc_app_id

    def get_uuc_merchant_key(self):
        return self.__uuc_merchant_key

    def get_uuc_secret_key(self):
        return self.__uuc_secret_key

    def get_wechat_app_id(self):
        return self.__wechat_app_id

    def get_wechat_merchant_id(self):
        return self.__wechat_merchant_id

    def get_special_data(self):
        return self.__special_data


    def get_plugin_lists_phone(self):
        return self.__plugin_lists_phone


    def set_b_up_path(self, b_up_path):
        self.__b_up_path = b_up_path

    def set_project_path(self, project_path):
        self.__project_path = project_path

    def set_dst_path(self, dst_path):
        self.__dst_path = dst_path

    def set_output_name(self):
        return self.__output_name

    def set_game_show_version(self, game_show_version):
        self.__game_show_version = game_show_version

    def set_game_version(self, game_version):
        self.__game_version = game_version

#     def set_package_name(self,package_name):
#         self.__package_name=package_name

    def set_package_name(self, screen_orientation):
        self.__screen_orientation = screen_orientation

    def set_package_name(self, avos_app_id):
        self.__avos_app_id = avos_app_id

    def set_package_name(self, avos_app_key):
        self.__avos_app_key = avos_app_key

    def set_show_app_name(self, show_app_name):
        self.__show_app_name = show_app_name

    def set_tbu_id(self, tbu_id):
        self.__tbu_id = tbu_id

    def set_poxiao_game_id(self, poxiao_game_id):
        self.__poxiao_game_id = poxiao_game_id

    def set_zhimeng_app_id(self, zhimeng_app_id):
        self.__zhimeng_app_id = zhimeng_app_id

    def set_zhimeng_merchant_id(self, zhimeng_merchant_id):
        self.__zhimeng_merchant_id = zhimeng_merchant_id

    def set_zhimeng_merchant_passwd(self, zhimeng_merchant_passwd):
        self.__zhimeng_merchant_passwd = zhimeng_merchant_passwd

    def set_letu_app_id(self, letu_app_id):
        self.__letu_app_id = letu_app_id

    def set_letu_merchant_id(self, letu_merchant_id):
        self.__letu_merchant_id = letu_merchant_id

    def set_letu_merchant_key(self, letu_merchant_key):
        self.__letu_merchant_key = letu_merchant_key

    def set_zhang_app_id(self,zhang_app_id):
        self.__zhang_app_id = zhang_app_id

    def set_zhang_key(self,zhang_key):
        self.__zhang_key = zhang_key

    def set_zhang_channel_id(self,zhang_channel_id):
        self.__zhang_channel_id = zhang_channel_id

    def set_uuc_app_id(self, uuc_app_id):
        self.__uuc_app_id = uuc_app_id

    def set_uuc_merchant_key(self,uuc_merchant_key):
        self.__uuc_merchant_key=uuc_merchant_key

    def set_uuc_secret_key(self,uuc_secret_key):
        self.__uuc_secret_key=uuc_secret_key

    def set_wechat_app_id(self, letu_app_id):
        self.__wechat_app_id = letu_app_id

    def set_wechat_merchant_id(self, letu_merchant_id):
        self.__wechat_merchant_id = letu_merchant_id

    def set_special_data(self, special_data):
        self.__special_data = special_data

    def set_px_ad(self, px_ad):
        self.__px_ad = px_ad

    def set_yt_ad(self, yt_ad):
        self.__px_ad = yt_ad

    def set_ox_ad(self, ox_ad):
        self.__ox_ad = ox_ad

    def set_save_path(self, save_path):
        self.__save_path = save_path

    def set_plugin_lists(self, plugin_lists):
        self.__plugin_lists = plugin_lists

    def set_client_order_id(self, client_order_id):
        self.__client_order_id = client_order_id

    def set_config_files_path(self, config_files_path):
        self.__config_files_path = config_files_path

    def set_PAY_SEQ_DEFAULT(self, PAY_SEQ_DEFAULT):
        self.__PAY_SEQ_DEFAULT = PAY_SEQ_DEFAULT

    def set_PAY_SEQ_CU(self, PAY_SEQ_CU):
        self.__PAY_SEQ_CU = PAY_SEQ_CU

    def set_PAY_SEQ_CT(self, PAY_SEQ_CT):
        self.__PAY_SEQ_CT = PAY_SEQ_CT

    def set_PAY_SEQ_CM(self, PAY_SEQ_CM):
        self.__PAY_SEQ_CM = PAY_SEQ_CM

    def set_other_libraries(self, other_libraries):
        self.__other_libraries = other_libraries

    def set_plugin_lists_phone(self,plugin_lists_phone):
        self.__plugin_lists_phone = plugin_lists_phone


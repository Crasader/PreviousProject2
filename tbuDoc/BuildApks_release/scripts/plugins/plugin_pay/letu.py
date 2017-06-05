  # letu
import urllib2
import urllib
import json
import sys
import os
import codecs
import shutil


class letu:
    def encryptJson(self, b_path,project_path):   
        startNO = content.find("<!-- letu config start -->")
        if '1030' in self._plugin_ids:
            if not os.path.exists(self._dst_path + "\\B\\libs\\lyhtghPayJar.jar"):
                shutil.copyfile(self._B_path + "\\B_LETU\\libs\\lyhtghPayJar.jar",
                                self._dst_path + "\\B\\libs\\lyhtghPayJar.jar")
            self.moveJar('b_letu_', self._dst_path + "\\B\\libs",
                         self._B_path + '\\B_LETU\\export')
            if startNO == -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- letu config end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\application\\letu.txt"), content, pos, "true")
                pos1 = content.find("</manifest>")
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- letu permission end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\letu.txt"), content, pos1, "true")

        elif '1030' not in self._plugin_ids:
            if os.path.exists(self._dst_path + "\\B\\libs\\lyhtghPayJar.jar"):
                os.remove(self._dst_path + "\\B\\libs\\lyhtghPayJar.jar")
            self.deleteJar("b_letu_", self._dst_path + "\\B\\libs")
            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- letu config end -->", "letu.txt", content, pos, "false")
                pos1 = content.find("</manifest>")
                startNO_letuPermission = content.find(
                    "<!-- letu permission start -->")
                if startNO_letuPermission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_letuPermission, "<!-- letu permission end -->", "", content, pos1, "false")

        # # unicome_zr
        # if '1040' in self._plugin_ids:
        #     self.moveJar('b_cu_', self._dst_path + "\\B\\libs",
        #                  self._B_path + '\\B_CU\\export')
        # else:
        #     self.deleteJar('b_cu_', self._dst_path + "\\B\\libs")
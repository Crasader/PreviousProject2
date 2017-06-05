# -*- coding: utf-8 -*-

from scripts.buildapk import buildapk
import sys
reload(sys)
sys.setdefaultencoding("utf-8")


if __name__ == "__main__":
  buildapk().build()
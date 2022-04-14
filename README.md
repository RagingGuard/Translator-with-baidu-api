# Translator-with-baidu-api
小翻译机 QT代码 使用百度翻译api（第一次开源，请多包含）
一、界面效果如下：
  ![捕获](https://user-images.githubusercontent.com/95950085/163393389-8c6e5c01-4054-45d6-9b49-5ea9fba01787.PNG)
![捕获1](https://user-images.githubusercontent.com/95950085/163393421-4998c679-7cf2-44cf-97a3-2484f1925ded.PNG)
2、使用方法
 ![捕获2](https://user-images.githubusercontent.com/95950085/163393442-f22cf06c-a7ba-4ba3-b5a0-adac76666ea8.PNG)
3、账号密码存储位置在
 ![捕获4](https://user-images.githubusercontent.com/95950085/163393465-ee63b0d5-4d7f-44a1-8c36-e1b4b7980542.PNG)
注意：
1、由于QT没有curl相关的操作，使用的是c库，所以需要增加如下库（已经在qt配置文件中设置）变异过程中出现需要增加库，直接根据提示安装对应程序即可（sudo apt-get install xxxxx）
LIBS += -lssl -lcurl -lcrypto
2、由于使用的免费的api，所以翻译时候会有诸多限制，例如超过一定字数就会自动忽略，或者敏感词汇就不会翻译


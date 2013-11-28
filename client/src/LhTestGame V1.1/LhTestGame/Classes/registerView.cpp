//
//  registerView.cpp
//  fengyanqi
//
//  Created by lh on 13-10-9.
//
//

#include "registerView.h"
#include "curl/curl.h"
static const char * messag="";
bool registerView::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150))){
        return false;
    }
    setTouchEnabled(true);
    size= CCDirector::sharedDirector()->getWinSize();
    CCSprite * bg= CCSprite::create("register_bg.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg);

    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(registerView::registerSuccess), "Register", NULL);
    
    CCMenuItemImage * btn1=CCMenuItemImage::create("register_up.png", "register_down.png", "register_up.png", this, menu_selector(registerView::menuCallBackRegister));

    CCMenuItemImage * btn2= CCMenuItemImage::create("close_up.png", "close_down.png", this, menu_selector(registerView::menuCallBackClose));
    btn2->setPosition(ccp(400, 300));
    btn1->setPosition(ccp(250, -100));
    menu=CCMenu::create(btn1,btn2,NULL);
    bg->addChild(menu);
    
    CCScale9Sprite * bg01=CCScale9Sprite::create();
    CCScale9Sprite * bg02=CCScale9Sprite::create();
    CCScale9Sprite * bg03=CCScale9Sprite::create();
    registerusername =CCEditBox::create(CCSizeMake(500, 60), bg01);
    registerusername->setText("");
    registerusername->setFontColor(ccc3(255, 255, 255));
    registerusername->setPosition(ccp(size.width/2+50,size.height/2+90));
    registerusername->setReturnType(kKeyboardReturnTypeDone);
    bg->addChild(registerusername);
    
    
    firPassword =CCEditBox::create(CCSizeMake(500, 60), bg02);
    firPassword->setText("");
    firPassword->setFontColor(ccc3(255, 255, 255));
    firPassword->setPosition(ccp(size.width/2+50,size.height/2));
    firPassword->setInputFlag(kEditBoxInputFlagPassword);
    firPassword->setReturnType(kKeyboardReturnTypeDone);
    bg->addChild(firPassword);
    secPassword =CCEditBox::create(CCSizeMake(500, 60), bg03);
    secPassword->setText("");
    secPassword->setInputFlag(kEditBoxInputFlagPassword);
    secPassword->setFontColor(ccc3(255, 255, 255));
    secPassword->setPosition(ccp(size.width/2+50,size.height/2-110));
    secPassword->setReturnType(kKeyboardReturnTypeDone);
    bg->addChild(secPassword);
    
    return true;
}
void registerView::registerSuccess(){
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "Register");
    CCMessageBox("注册成功", "成 功");
    this->removeFromParent();
    
}
void registerView::menuCallBackClose(){
    this->removeFromParent();
}
void registerView::menuCallBackRegister(){
    std::string str= firPassword->getText();
    std::string str2= secPassword->getText();
    if (!strcmp(str.c_str(), str2.c_str())&&strcmp(firPassword->getText(), "")&&strcmp(secPassword->getText(), "")&&strcmp(registerusername->getText(), "")) {
        CURL *curl;
        CURLcode res;
        //http协议
        
        curl = curl_easy_init();
        if (curl)
        {
            char ipstr[100]="";
  
            

            sprintf(ipstr, "http://172.16.21.19:11008/register?username=%s&password=%s",registerusername->getText(),secPassword->getText());
            CCLog("%s",ipstr);
            char output[500]="";
            curl_easy_setopt(curl, CURLOPT_URL, ipstr);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, process_data);
            CCLog("%s",output);

            res = curl_easy_perform(curl);

            if(res==0){

                
            }else{
                
            }
            curl_easy_cleanup(curl); 
            
        }
    }else{
        CCMessageBox("出错了！", "出错了");
    }
}

size_t registerView::process_data(void *buffer, size_t size, size_t nmemb, void *user_p){
    FILE *fp = (FILE *)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    
    messag=(char *)buffer;
    CCNotificationCenter::sharedNotificationCenter()->postNotification("Register");
    std::cout << (char *)buffer << std::endl;
    return return_size;
}
void  registerView::registerWithTouchDispatcher(){
     CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-9999, true);
     CCLayer::registerWithTouchDispatcher();
}

bool registerView::ccTouchBegan(CCTouch* touch, CCEvent* event){
    registerBool = registerusername->ccTouchBegan(touch, event);
    menuflag=menu->ccTouchBegan(touch, event);
    firFlag= firPassword->ccTouchBegan(touch, event);
    secFlag= secPassword->ccTouchBegan(touch, event);
    return true;
}
void registerView::ccTouchMoved(CCTouch* touch, CCEvent* event){
    if(registerBool){
        registerusername->ccTouchMoved(touch, event);
    }
    if(menuflag){
        menu->ccTouchMoved(touch, event);
    }
    if(firFlag){
        firPassword->ccTouchMoved(touch, event);
    }
    if(secFlag){
        secPassword->ccTouchMoved(touch, event);
    }
}
void registerView::ccTouchEnded(CCTouch* touch, CCEvent* event){
    if(registerBool){
        registerusername->ccTouchEnded(touch, event);
        registerBool=false;
    }
    if(menuflag){
        menu->ccTouchEnded(touch, event);
        menuflag=false;
    }
    if(firFlag){
        firPassword->ccTouchEnded(touch, event);
        firFlag=false;
    }
    if(secFlag){
        secPassword->ccTouchEnded(touch, event);
        secFlag=false;
    }
}



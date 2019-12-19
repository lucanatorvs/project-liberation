/**
 *  AutoConnect portal site web page implementation.
 *  @file   AutoConnectPage.h
 *  @author hieromon@gmail.com
 *  @version    1.1.0
 *  @date   2019-10-15
 *  @copyright  MIT license.
 */

#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
extern "C" {
#include <user_interface.h>
}
#elif defined(ARDUINO_ARCH_ESP32)
#include <esp_spi_flash.h>
#include <WiFi.h>
#define ENC_TYPE_NONE WIFI_AUTH_OPEN
#endif
#include "AutoConnect.h"
#include "AutoConnectPage.h"
#include "AutoConnectCredential.h"

/**< Basic CSS common to all pages */
const char AutoConnect::_CSS_BASE[] PROGMEM = {
  "html{"
    "font-family:Helvetica,Arial,sans-serif;"
    "font-size:16px;"
    "-ms-text-size-adjust:100%;"
    "-webkit-text-size-adjust:100%;"
    "-moz-osx-font-smoothing:grayscale;"
    "-webkit-font-smoothing:antialiased"
  "}"
  "body{"
    "margin:0;"
    "padding:0"
  "}"
  ".base-panel{"
    "margin:0 22px 0 22px"
  "}"
  ".base-panel * label :not(.bins){"
    "display:inline-block;"
    "width:3.0em;"
    "text-align:right"
  "}"
  ".base-panel * .slist{"
    "width:auto;"
    "font-size:0.9em;"
    "margin-left:10px;"
    "text-align:left"
  "}"
  "input{"
    "-moz-appearance:none;"
    "-webkit-appearance:none;"
    "font-size:0.9em;"
    "margin:8px 0 auto"
  "}"
  ".lap{"
    "visibility:collapse"
  "}"
  ".lap:target{"
    "visibility:visible"
  "}"
  ".lap:target .overlap{"
    "opacity:0.7;"
    "transition:0.3s"
  "}"
  ".lap:target .modal_button{"
    "opacity:1;"
    "transition:0.3s"
  "}"
  ".overlap{"
    "top:0;"
    "left:0;"
    "width:100%;"
    "height:100%;"
    "position:fixed;"
    "opacity:0;"
    "background:#000;"
    "z-index:1000"
  "}"
  ".modal_button{"
    "border-radius:13px;"
    "background:#660033;"
    "color:#ffffcc;"
    "padding:20px 30px;"
    "text-align:center;"
    "text-decoration:none;"
    "letter-spacing:1px;"
    "font-weight:bold;"
    "display:inline-block;"
    "top:40%;"
    "left:40%;"
    "width:20%;"
    "position:fixed;"
    "opacity:0;"
    "z-index:1001"
  "}"
};

/**< non-marked list for UL */
const char AutoConnect::_CSS_UL[] PROGMEM = {
  ".noorder,.exp{"
    "padding:0;"
    "list-style:none;"
    "display:table"
  "}"
  ".noorder li,.exp{"
    "display:table-row-group"
  "}"
  ".noorder li label, .exp li *{"
    "display:table-cell;"
    "width:auto;"
    "text-align:right;"
    "padding:10px 0.5em"
  "}"
  ".noorder input[type=\"checkbox\"]{"
    "-moz-appearance:checkbox;"
    "-webkit-appearance:checkbox"
  "}"
  ".noorder input[type=\"radio\"]{"
    "margin-right:0.5em;"
    "-moz-appearance:radio;"
    "-webkit-appearance:radio"
  "}"
  ".noorder input[type=\"text\"]{"
    "width:auto"
  "}"
  ".noorder input[type=\"text\"]:invalid{"
    "background:#fce4d6"
  "}"
};

/**< Image icon for inline expansion, the lock mark. */
const char AutoConnect::_CSS_ICON_LOCK[] PROGMEM = {
  ".img-lock{"
    "display:inline-block;"
    "width:22px;"
    "height:22px;"
    "margin-top:14px;"
    "float:right;"
    "background: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAACXBIWXMAAAsTAAALEwEAmpwYAAAB1ElEQVRIibWVu0scURTGf3d2drBQFAWbbRQVCwuVLIZdi2gnWIiF/4GtKyuJGAJh8mgTcU0T8T8ICC6kiIVu44gvtFEQQWwsbExQJGHXmZtiZsOyzCN3Vz+4cDjfvec7j7l3QAF95onRZ54YKmdE1IbnS0c9mnAyAjkBxDy3LRHrjtRyu7OD52HntTAyvbw/HxP2hkCearrRb2WSCSuTTGi60S+QpzFhbwznDl/VVMHw0sF7hEjFbW2qkB38lfp8nNDipWcATil+uDM3cDWyeNRSijnfkHJnezb5Vkkgvbg3IOXD2e1ts93S+icnkZOAVaalZK3YQMa4L+pC6L1WduhYSeCf0PLBdxzOjZ93Lwvm6APAiLmlF1ubPiHotmaS41ExQjH0ZbfNM1NAFpgD0lVcICIrANqAVaAd+AFIYAy4BqaBG+Wsq5AH3vgk8xpYrzf4KLAZwhe8PYEIvQe4vc6H8Hnc2dQs0AFchvAXQGdEDF8s4A5TZS34BQqqQNaS1WMI3KD4WUbNoBJfce9CO7BSr4BfBe8A21vmUwh0VdjdTyHwscL+UK+AHxoD7FDoAX6/Cnpxn4ay/egCjcCL/w1chkqLakLQ/6ABhT57uAd+Vzv/Ara3iY6fK4WxAAAAAElFTkSuQmCC) no-repeat"
  "}"
};

/**< INPUT button and submit style */
const char AutoConnect::_CSS_INPUT_BUTTON[] PROGMEM = {
  "input[type=\"button\"],input[type=\"submit\"],button[type=\"submit\"],button[type=\"button\"]{"
    "padding:8px 0.5em;"
    "font-weight:bold;"
    "letter-spacing:0.8px;"
    "color:#fff;"
    "border:1px solid;"
    "border-radius:2px;"
    "margin-top:12px"
  "}"
  "input[type=\"button\"],button[type=\"button\"]{"
    "background-color:#1b5e20;"
    "border-color:#1b5e20;"
    "width:15em"
  "}"
  ".aux-page input[type=\"button\"],button[type=\"button\"]{"
    "font-weight:normal;"
    "padding:8px 14px;"
    "margin:12px;"
    "width:auto"
  "}"
  "input#sb[type=\"submit\"]{"
    "width:15em"
  "}"
  "input[type=\"submit\"],button[type=\"submit\"]{"
    "padding:8px 30px;"
    "background-color:#006064;"
    "border-color:#006064"
  "}"
  "input[type=\"button\"],input[type=\"submit\"],button[type=\"submit\"]:focus,"
  "input[type=\"button\"],input[type=\"submit\"],button[type=\"submit\"]:active{"
    "outline:none;"
    "text-decoration:none"
  "}"
};

/**< INPUT text style */
const char AutoConnect::_CSS_INPUT_TEXT[] PROGMEM = {
  "input[type=\"text\"],input[type=\"password\"], .aux-page select{"
    "background-color:#fff;"
    "border:1px solid #ccc;"
    "border-radius:2px;"
    "color:#444;"
    "margin:8px 0 8px 0;"
    "padding:10px"
  "}"
  "input[type=\"text\"],input[type=\"password\"]{"
    "font-weight:300;"
    "width:auto;"
    "-webkit-transition:all 0.20s ease-in;"
    "-moz-transition:all 0.20s ease-in;"
    "-o-transition:all 0.20s ease-in;"
    "-ms-transition:all 0.20s ease-in;"
    "transition:all 0.20s ease-in"
  "}"
  "input[type=\"text\"]:focus,input[type=\"password\"]:focus{"
    "outline:none;"
    "border-color:#5C9DED;"
    "box-shadow:0 0 3px #4B8CDC"
  "}"
  "input.error,input.error:focus{"
    "border-color:#ED5564;"
    "color:#D9434E;"
    "box-shadow:0 0 3px #D9434E"
  "}"
  "input:disabled{"
    "opacity:0.6;"
    "background-color:#f7f7f7"
  "}"
  "input:disabled:hover{"
    "cursor:not-allowed"
  "}"
  "input.error::-webkit-input-placeholder,"
  "input.error::-moz-placeholder,"
  "input.error::-ms-input-placeholder{"
    "color:#D9434E"
  "}"
  ".aux-page label{"
    "display:inline;"
    "padding:10px 0.5em;"
  "}"
};

/**< TABLE style */
const char AutoConnect::_CSS_TABLE[] PROGMEM = {
  "table{"
    "border-collapse:collapse;"
    "border-spacing:0;"
    "border:1px solid #ddd;"
    "color:#444;"
    "background-color:#fff;"
    "margin-bottom:20px"
  "}"
  "table.info,"
  "table.info>tfoot,"
  "table.info>thead{"
    "width:100%;"
    "border-color:#5C9DED"
  "}"
  "table.info>thead{"
    "background-color:#5C9DED"
  "}"
  "table.info>thead>tr>th{"
    "color:#fff"
  "}"
  "td,"
  "th{"
    "padding:10px 22px"
  "}"
  "thead{"
    "background-color:#f3f3f3;"
    "border-bottom:1px solid #ddd"
  "}"
  "thead>tr>th{"
    "font-weight:400;"
    "text-align:left"
  "}"
  "tfoot{"
    "border-top:1px solid #ddd"
  "}"
  "tbody,"
  "tbody>tr:nth-child(odd){"
    "background-color:#fff"
  "}"
  "tbody>tr>td,"
  "tfoot>tr>td{"
    "font-weight:300;"
    "font-size:.88em"
  "}"
  "tbody>tr:nth-child(even){"
    "background-color:#f7f7f7"
  "}"
    "table.info tbody>tr:nth-child(even){"
    "background-color:#EFF5FD"
  "}"
};

/**< SVG animation for spinner */
const char AutoConnect::_CSS_SPINNER[] PROGMEM = {
  ".spinner{"
    "width:40px;"
    "height:40px;"
    "position:relative;"
    "margin:100px auto"
  "}"
  ".dbl-bounce1, .dbl-bounce2{"
    "width:100%;"
    "height:100%;"
    "border-radius:50%;"
    "background-color:#a3cccc;"
    "opacity:0.6;"
    "position:absolute;"
    "top:0;"
    "left:0;"
    "-webkit-animation:sk-bounce 2.0s infinite ease-in-out;"
    "animation:sk-bounce 2.0s infinite ease-in-out"
  "}"
  ".dbl-bounce2{"
    "-webkit-animation-delay:-1.0s;"
    "animation-delay:-1.0s"
  "}"
  "@-webkit-keyframes sk-bounce{"
    "0%, 100%{-webkit-transform:scale(0.0)}"
    "50%{-webkit-transform:scale(1.0)}"
  "}"
  "@keyframes sk-bounce{"
    "0%,100%{"
      "transform:scale(0.0);"
      "-webkit-transform:scale(0.0);"
    "}50%{"
      "transform:scale(1.0);"
      "-webkit-transform:scale(1.0);"
    "}"
  "}"
};

/**< Common menu bar. This style quotes LuxBar. */
/**< balzss/luxbar is licensed under the MIT License https://github.com/balzss/luxbar */
const char AutoConnect::_CSS_LUXBAR[] PROGMEM = {
  ".lb-fixed{"
    "width:100%;"
    "position:fixed;"
    "top:0;"
    "left:0;"
    "z-index:1000;"
    "box-shadow:0 1px 3px rgba(0, 0, 0, 0.12), 0 1px 2px rgba(0, 0, 0, 0.24)"
  "}"
  ".lb-burger span,"
  ".lb-burger span::before,"
  ".lb-burger span::after{"
    "display:block;"
    "height:2px;"
    "width:26px;"
    "transition:0.6s ease"
  "}"
  ".lb-cb:checked~.lb-menu li .lb-burger span{"
    "background-color:transparent"
  "}"
  ".lb-cb:checked~.lb-menu li .lb-burger span::before,"
  ".lb-cb:checked~.lb-menu li .lb-burger span::after{"
    "margin-top:0"
  "}"
  ".lb-header{"
    "display:flex;"
    "flex-direction:row;"
    "justify-content:space-between;"
    "align-items:center;"
    "height:58px"
  "}"
  ".lb-menu-right .lb-burger{"
    "margin-left:auto"
  "}"
  ".lb-brand{"
    "font-size:1.6em;"
    "padding:18px 24px 18px 24px"
  "}"
  ".lb-menu{"
    "min-height:58px;"
    "transition:0.6s ease;"
    "width:100%"
  "}"
  ".lb-navigation{"
    "display:flex;"
    "flex-direction:column;"
    "list-style:none;"
    "padding-left:0;"
    "margin:0"
  "}"
  ".lb-menu a,"
  ".lb-item a{"
    "text-decoration:none;"
    "color:inherit;"
    "cursor:pointer"
  "}"
  ".lb-item{"
    "height:58px"
  "}"
  ".lb-item a{"
    "padding:18px 24px 18px 24px;"
    "display:block"
  "}"
  ".lb-burger{"
    "padding:18px 24px 18px 24px;"
    "position:relative;"
    "cursor:pointer"
  "}"
  ".lb-burger span::before,"
  ".lb-burger span::after{"
    "content:'';"
    "position:absolute"
  "}"
  ".lb-burger span::before{"
    "margin-top:-8px"
  "}"
  ".lb-burger span::after{"
    "margin-top:8px"
  "}"
  ".lb-cb{"
    "display:none"
  "}"
  ".lb-cb:not(:checked)~.lb-menu{"
    "overflow:hidden;"
    "height:58px"
  "}"
  ".lb-cb:checked~.lb-menu{"
    "transition:height 0.6s ease;"
    "height:100vh;"
    "overflow:auto"
  "}"
  ".dropdown{"
    "position:relative;"
    "height:auto;"
    "min-height:58px"
  "}"
  ".dropdown:hover>ul{"
    "position:relative;"
    "display:block;"
    "min-width:100%"
  "}"
  ".dropdown>a::after{"
    "position:absolute;"
    "content:'';"
    "right:10px;"
    "top:25px;"
    "border-width:5px 5px 0;"
    "border-color:transparent;"
    "border-style:solid"
  "}"
  ".dropdown>ul{"
    "display:block;"
    "overflow-x:hidden;"
    "list-style:none;"
    "padding:0"
  "}"
  ".dropdown>ul .lb-item{"
    "min-width:100%;"
    "height:29px;"
    "padding:5px 10px 5px 40px"
  "}"
  ".dropdown>ul .lb-item a{"
    "min-height:29px;"
    "line-height:29px;"
    "padding:0"
  "}"
  "@media screen and (min-width:768px){"
    ".lb-navigation{"
      "flex-flow:row;"
      "justify-content:flex-end;"
    "}"
    ".lb-burger{"
      "display:none;"
    "}"
    ".lb-cb:not(:checked)~.lb-menu{"
      "overflow:visible;"
    "}"
    ".lb-cb:checked~.lb-menu{"
      "height:58px;"
    "}"
    ".lb-menu .lb-item{"
      "border-top:0;"
    "}"
    ".lb-menu-right .lb-header{"
      "margin-right:auto;"
    "}"
    ".dropdown{"
      "height:58px;"
    "}"
    ".dropdown:hover>ul{"
      "position:absolute;"
      "left:0;"
      "top:58px;"
      "padding:0;"
    "}"
    ".dropdown>ul{"
      "display:none;"
    "}"
    ".dropdown>ul .lb-item{"
      "padding:5px 10px;"
    "}"
    ".dropdown>ul .lb-item a{"
      "white-space:nowrap;"
    "}"
  "}"
  ".lb-cb:checked+.lb-menu .lb-burger-dblspin span::before{"
    "transform:rotate(225deg)"
  "}"
  ".lb-cb:checked+.lb-menu .lb-burger-dblspin span::after{"
    "transform:rotate(-225deg)"
  "}"
  ".lb-menu-material,"
  ".lb-menu-material .dropdown ul{"
    "background-color:" AUTOCONNECT_MENUCOLOR_BACKGROUND ";"
    "color:" AUTOCONNECT_MENUCOLOR_TEXT
  "}"
  ".lb-menu-material .active,"
  ".lb-menu-material .lb-item:hover{"
    "background-color:" AUTOCONNECT_MENUCOLOR_ACTIVE
  "}"
  ".lb-menu-material .lb-burger span,"
  ".lb-menu-material .lb-burger span::before,"
  ".lb-menu-material .lb-burger span::after{"
    "background-color:" AUTOCONNECT_MENUCOLOR_TEXT
  "}"
};

/**< Common html document header. */
const char AutoConnect::_ELM_HTML_HEAD[] PROGMEM = {
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "<meta charset=\"UTF-8\" name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
};

/**< LuxBar menu element. */
const char  AutoConnect::_ELM_MENU_PRE[] PROGMEM = {
  "<header id=\"lb\" class=\"lb-fixed\">"
    "<input type=\"checkbox\" class=\"lb-cb\" id=\"lb-cb\"/>"
    "<div class=\"lb-menu lb-menu-right lb-menu-material\">"
      "<ul class=\"lb-navigation\">"
        "<li class=\"lb-header\">"
          "<a href=\"" AUTOCONNECT_URI "\" class=\"lb-brand\">MENU_TITLE</a>"
          "<label class=\"lb-burger lb-burger-dblspin\" id=\"lb-burger\" for=\"lb-cb\"><span></span></label>"
        "</li>"
        //"<li class=\"lb-item\"><a href=\"" AUTOCONNECT_URI_CONFIG "\">" AUTOCONNECT_MENULABEL_CONFIGNEW "</a></li>"
        //"<li class=\"lb-item\"><a href=\"" AUTOCONNECT_URI_OPEN "\">" AUTOCONNECT_MENULABEL_OPENSSIDS "</a></li>"
        //"<li class=\"lb-item\"><a href=\"" AUTOCONNECT_URI_DISCON "\">" AUTOCONNECT_MENULABEL_DISCONNECT "</a></li>"
        //"<li class=\"lb-item\" id=\"reset\"><a href=\"#rdlg\">" AUTOCONNECT_MENULABEL_RESET "</a></li>"
};

const char  AutoConnect::_ELM_MENU_AUX[] PROGMEM = {
        "{{AUX_MENU}}"
};

const char  AutoConnect::_ELM_MENU_POST[] PROGMEM = {
        "<li class=\"lb-item\" id=\"reset\"><a href=\"#rdlg\">" AUTOCONNECT_MENULABEL_RESET "</a></li>"
        //"<li class=\"lb-item\"><a href=\"HOME_URI\">" AUTOCONNECT_MENULABEL_HOME "</a></li>"
      "</ul>"
    "</div>"
    "<div class=\"lap\" id=\"rdlg\"><a href=\"#reset\" class=\"overlap\"></a>"
      "<div class=\"modal_button\"><h2><a href=\"" AUTOCONNECT_URI_RESET "\" class=\"modal_button\">" AUTOCONNECT_BUTTONLABEL_RESET "</a></h2></div>"
    "</div>"
  "</header>"
};

/**< The 404 page content. */
const char  AutoConnect::_PAGE_404[] PROGMEM = {
  "{{HEAD}}"
    "<title>Page not found</title>"
  "</head>"
  "<body>"
    "404 Not found"
  "</body>"
  "</html>"
};

/**< The page that started the reset. */
const char  AutoConnect::_PAGE_RESETTING[] PROGMEM = {
  "{{HEAD}}"
    "<meta http-equiv=\"refresh\" content=\"{{UPTIME}};url={{BOOTURI}}\">"
    "<title>AutoConnect resetting</title>"
  "</head>"
  "<body>"
    "<h2>{{RESET}}</h2>"
  "</body>"
  "</html>"
};

/**< AutoConnect portal page. */
const char  AutoConnect::_PAGE_STAT[] PROGMEM = {
  "{{HEAD}}"
    "<title>AutoConnect home</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_ICON_LOCK}}"
      "{{CSS_INPUT_BUTTON}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_AUX}}"
      "{{MENU_POST}}"
      "<div class=\"base-panel\">"
        "<p style=\"font-family:Arial;font-size:18px;font-weight:400;color:#191970\">Welkom bij de <b>WOW-Monitor v1.0</b>. dit slimme weerstation meet de luchtdruk, temperatuur en luchtvochtigheid en upload dit naar de cloud zodat dit op de WOW-site van het KNMI te zien is. Door dit menu kunt u uw weerstation koppelen.</p>"  
        "<form action=\"\\wow-settings\">"
          "<input type=\"submit\" value=\"Start configuratie\">"
        "</form>"
        "<p style=\"font-family:Arial;font-size:12px;font-weight:400;color:#000000\">Gemaakt door: Bob Swinkels en Luca van Straaten</p>"  
        "<img src=\"data:image/png;base64,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\" style=\"max-width: 200px; width:80%; margin: 20px auto; display: block;\" >"
      "</div>"
    "</div>"
  "</body>"
  "</html>"
};

/**< A page that specifies the new configuration. */
const char  AutoConnect::_PAGE_CONFIGNEW[] PROGMEM = {
  "{{HEAD}}"
    "<title>AutoConnect config</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_ICON_LOCK}}"
      "{{CSS_UL}}"
      "{{CSS_INPUT_BUTTON}}"
      "{{CSS_INPUT_TEXT}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_AUX}}"
      "{{MENU_POST}}"
      "<div class=\"base-panel\">"
        "<form action=\"" AUTOCONNECT_URI_CONNECT "\" method=\"post\">"
          "{{LIST_SSID}}"
          "<div style=\"margin:16px 0 8px 0;border-bottom:solid 1px #263238;\">Total:{{SSID_COUNT}} Hidden:{{HIDDEN_COUNT}}</div>"
          "<ul class=\"noorder\">"
            "<li>"
              "<label for=\"ssid\">SSID</label>"
              "<input id=\"ssid\" type=\"text\" name=\"" AUTOCONNECT_PARAMID_SSID "\" placeholder=\"SSID\">"
            "</li>"
            "<li>"
              "<label for=\"passphrase\">Passphrase</label>"
              "<input id=\"passphrase\" type=\"password\" name=\"" AUTOCONNECT_PARAMID_PASS "\" placeholder=\"Passphrase\">"
            "</li>"
            "<li>"
              "<label for=\"dhcp\">Enable DHCP</label>"
              "<input id=\"dhcp\" type=\"checkbox\" name=\"dhcp\" value=\"en\" checked onclick=\"vsw(this.checked);\">"
            "</li>"
            "{{CONFIG_IP}}"
            "<li><input type=\"submit\" value=\"Apply\"></li>"
          "</ul>"
        "</form>"
      "</div>"
    "</div>"
  "<script type=\"text/javascript\">"
    "window.onload=function(){"
      "['" AUTOCONNECT_PARAMID_STAIP "','" AUTOCONNECT_PARAMID_GTWAY "','" AUTOCONNECT_PARAMID_NTMSK "','" AUTOCONNECT_PARAMID_DNS1 "','" AUTOCONNECT_PARAMID_DNS2 "'].forEach(function(n,o,t){"
        "io=document.getElementById(n),io.placeholder='0.0.0.0',io.pattern='^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$'});"
      "vsw(true)};"
    "function onFocus(e){"
      "document.getElementById('ssid').value=e,document.getElementById('passphrase').focus()"
    "}"
    "function vsw(e){"
      "var t;t=e?'none':'table-row';for(const e of document.getElementsByClassName('exp'))e.style.display=t;e||document.getElementById('sip').focus()"
    "}"
  "</script>"
  "</body>"
  "</html>"
};

/**< A page that reads stored authentication information and starts connection. */
const char  AutoConnect::_PAGE_OPENCREDT[] PROGMEM = {
  "{{HEAD}}"
    "<title>AutoConnect credentials</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_ICON_LOCK}}"
      "{{CSS_INPUT_BUTTON}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_AUX}}"
      "{{MENU_POST}}"
      "<div class=\"base-panel\">"
        "<form action=\"" AUTOCONNECT_URI_CONNECT "\" method=\"post\">"
          "{{OPEN_SSID}}"
        "</form>"
        "<form action=\"" AUTOCONNECT_URI_CONFIG "\">"
          "<input type=\"submit\" value=\"Zoek meer netwerken\">"
        "</form>"
      "</div>"
    "</div>"
  "</body>"
  "</html>"
};

/**< A page that informs during a connection attempting. */
const char  AutoConnect::_PAGE_CONNECTING[] PROGMEM = {
  "{{REQ}}"
  "{{HEAD}}"
    "<title>AutoConnect connecting</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_SPINNER}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_POST}}"
      "<div class=\"spinner\">"
        "<div class=\"dbl-bounce1\"></div>"
        "<div class=\"dbl-bounce2\"></div>"
        "<div style=\"position:absolute;left:-100%;right:-100%;text-align:center;margin:10px auto;font-weight:bold;color:#0b0b33;\">{{CUR_SSID}}</div>"
      "</div>"
    "</div>"
    "<script type=\"text/javascript\">"
      "setTimeout(\"link()\"," AUTOCONNECT_RESPONSE_WAITTIME ");"
      "function link(){location.href='" AUTOCONNECT_URI_RESULT "';}"
    "</script>"
  "</body>"
  "</html>"
};

/**< A page announcing that a connection has been established. */
const char  AutoConnect::_PAGE_SUCCESS[] PROGMEM = {
  "{{HEAD}}"
    "<title>AutoConnect statistics</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_TABLE}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_AUX}}"
      "{{MENU_POST}}"
      "<div class=\"base-panel\">"
        "<p style=\"font-family:Arial;font-size:18px;font-weight:400;color:#191970\">De verbinding met de WiFi is succesvol. Deze site sluit nu en het weerstation wordt in werking gesteld.</p>"  
      "</div>"
    "</div>"
  "</body>"
  "</html>"
};

/**< A response page for connection failed. */
const char  AutoConnect::_PAGE_FAIL[] PROGMEM = {
  "{{HEAD}}"
    "<title>AutoConnect statistics</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_TABLE}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_AUX}}"
      "{{MENU_POST}}"
      "<div>"
        "<table class=\"info\" style=\"border:none;\">"
          "<tbody>"
          "<tr>"
            "<td>Connection Failed</td>"
            "<td>{{STATION_STATUS}}</td>"
          "</tr>"
          "</tbody>"
        "</table>"
      "</div>"
    "</div>"
  "</body>"
  "</html>"
};

/**< A response page for disconnected from the AP. */
const char  AutoConnect::_PAGE_DISCONN[] PROGMEM = {
  "{{DISCONNECT}}"
  "{{HEAD}}"
    "<title>AutoConnect disconnected</title>"
    "<style type=\"text/css\">"
      "{{CSS_BASE}}"
      "{{CSS_LUXBAR}}"
    "</style>"
  "</head>"
  "<body style=\"padding-top:58px;\">"
    "<div class=\"container\">"
      "{{MENU_PRE}}"
      "{{MENU_POST}}"
    "</div>"
  "</body>"
  "</html>"
};

// Each page of AutoConnect is http transferred by the content transfer
// mode of Page Builder. The default transfer mode is
// AUTOCONNECT_HTTP_TRANSFER defined in AutoConnectDefs.h. The page to
// which default transfer mode is not applied, specifies the enumeration
// value of PageBuilder::TransferEncoding_t. The content construction
// buffer can be reserved with the chunked transfer, and its size is
// macro defined by AUTOCONNECT_CONTENTBUFFER_SIZE.
const AutoConnect::PageTranserModeST AutoConnect::_pageBuildMode[] = {
  { AUTOCONNECT_URI,         AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_CONFIG,  PB_Chunk, AUTOCONNECT_CONTENTBUFFER_SIZE },
  { AUTOCONNECT_URI_CONNECT, AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_RESULT,  AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_OPEN,    AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_DISCON,  AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_RESET,   AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_SUCCESS, AUTOCONNECT_HTTP_TRANSFER, 0 },
  { AUTOCONNECT_URI_FAIL,    AUTOCONNECT_HTTP_TRANSFER, 0 }
};

uint32_t AutoConnect::_getChipId() {
#if defined(ARDUINO_ARCH_ESP8266)
  return ESP.getChipId();
#elif defined(ARDUINO_ARCH_ESP32)
  uint64_t  chipId;
  chipId = ESP.getEfuseMac();
  return (uint32_t)(chipId >> 32);
#endif
}

uint32_t AutoConnect::_getFlashChipRealSize() {
#if defined(ARDUINO_ARCH_ESP8266)
  return ESP.getFlashChipRealSize();
#elif defined(ARDUINO_ARCH_ESP32)
  return (uint32_t)spi_flash_get_chip_size();
#endif
}

String AutoConnect::_token_CSS_BASE(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_BASE));
}

String AutoConnect::_token_CSS_UL(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_UL));
}

String AutoConnect::_token_CSS_ICON_LOCK(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_ICON_LOCK));
}

String AutoConnect::_token_CSS_INPUT_BUTTON(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_INPUT_BUTTON));
}

String AutoConnect::_token_CSS_INPUT_TEXT(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_INPUT_TEXT));
}

String AutoConnect::_token_CSS_TABLE(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_TABLE));
}

String AutoConnect::_token_CSS_SPINNER(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_SPINNER));
}

String AutoConnect::_token_HEAD(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_ELM_HTML_HEAD));
}

String AutoConnect::_token_MENU_PRE(PageArgument& args) {
  String  currentMenu = FPSTR(_ELM_MENU_PRE);
  currentMenu.replace(String(F("MENU_TITLE")), _menuTitle);
  currentMenu.replace(String(F("{{CUR_SSID}}")), _token_ESTAB_SSID(args));
  return currentMenu;
}

String AutoConnect::_token_MENU_AUX(PageArgument& args) {
  String  menuItem = String("");
  if (_aux)
    menuItem = _aux->_injectMenu(args);
  return menuItem;
}

String AutoConnect::_token_MENU_POST(PageArgument& args) {
  AC_UNUSED(args);
  String  postMenu = FPSTR(_ELM_MENU_POST);
  postMenu.replace(String(F("HOME_URI")), _apConfig.homeUri);
  return postMenu;
}

String AutoConnect::_token_CSS_LUXBAR(PageArgument& args) {
  AC_UNUSED(args);
  return String(FPSTR(_CSS_LUXBAR));
}

String AutoConnect::_token_ESTAB_SSID(PageArgument& args) {
  AC_UNUSED(args);
  return (WiFi.status() == WL_CONNECTED ? WiFi.SSID() : String(F("N/A")));
}

String AutoConnect::_token_WIFI_MODE(PageArgument& args) {
  AC_UNUSED(args);
  const char* wifiMode = "";
  switch (WiFi.getMode()) {
  case WIFI_OFF:
    wifiMode = "OFF";
    break;
  case WIFI_STA:
    wifiMode = "STA";
    break;
  case WIFI_AP:
    wifiMode = "AP";
    break;
  case WIFI_AP_STA:
    wifiMode = "AP_STA";
    break;
#ifdef ARDUINO_ARCH_ESP32
  case WIFI_MODE_MAX:
    wifiMode = "MAX";
    break;
#endif
  }
  return String(wifiMode);
}

String AutoConnect::_token_WIFI_STATUS(PageArgument& args) {
  AC_UNUSED(args);
  return String(WiFi.status());
}

String AutoConnect::_token_STATION_STATUS(PageArgument& args) {
  AC_UNUSED(args);
  PGM_P wlStatusSymbol = PSTR("");
  // const char* wlStatusSymbol ="";
  PGM_P wlStatusSymbols[] = {
  // static const char* wlStatusSymbols[] = {
#if defined(ARDUINO_ARCH_ESP8266)
    PSTR("IDLE"),
    PSTR("CONNECTING"),
    PSTR("WRONG_PASSWORD"),
    PSTR("NO_AP_FOUND"),
    PSTR("CONNECT_FAIL"),
    PSTR("GOT_IP")
  };
  switch (wifi_station_get_connect_status()) {
  case STATION_IDLE:
    wlStatusSymbol = wlStatusSymbols[0];
    break;
  case STATION_CONNECTING:
    wlStatusSymbol = wlStatusSymbols[1];
    break;
  case STATION_WRONG_PASSWORD:
    wlStatusSymbol = wlStatusSymbols[2];
    break;
  case STATION_NO_AP_FOUND:
    wlStatusSymbol = wlStatusSymbols[3];
    break;
  case STATION_CONNECT_FAIL:
    wlStatusSymbol = wlStatusSymbols[4];
    break;
  case STATION_GOT_IP:
    wlStatusSymbol = wlStatusSymbols[5];
    break;
#elif defined(ARDUINO_ARCH_ESP32)
    PSTR("IDLE"),
    PSTR("NO_SSID_AVAIL"),
    PSTR("SCAN_COMPLETED"),
    PSTR("CONNECTED"),
    PSTR("CONNECT_FAILED"),
    PSTR("CONNECTION_LOST"),
    PSTR("DISCONNECTED"),
    PSTR("NO_SHIELD")
  };
  switch (_rsConnect) {
  case WL_IDLE_STATUS:
    wlStatusSymbol = wlStatusSymbols[0];
    break;
  case WL_NO_SSID_AVAIL:
    wlStatusSymbol = wlStatusSymbols[1];
    break;
  case WL_SCAN_COMPLETED:
    wlStatusSymbol = wlStatusSymbols[2];
    break;
  case WL_CONNECTED:
    wlStatusSymbol = wlStatusSymbols[3];
    break;
  case WL_CONNECT_FAILED:
    wlStatusSymbol = wlStatusSymbols[4];
    break;
  case WL_CONNECTION_LOST:
    wlStatusSymbol = wlStatusSymbols[5];
    break;
  case WL_DISCONNECTED:
    wlStatusSymbol = wlStatusSymbols[6];
    break;
  case WL_NO_SHIELD:
    wlStatusSymbol = wlStatusSymbols[7];
    break;
#endif
  }
  return String("(") + String(_rsConnect) + String(") ") + String(FPSTR(wlStatusSymbol));
}

String AutoConnect::_token_LOCAL_IP(PageArgument& args) {
  AC_UNUSED(args);
  return WiFi.localIP().toString();
}

String AutoConnect::_token_SOFTAP_IP(PageArgument& args) {
  AC_UNUSED(args);
  return WiFi.softAPIP().toString();
}

String AutoConnect::_token_GATEWAY(PageArgument& args) {
  AC_UNUSED(args);
  return WiFi.gatewayIP().toString();
}

String AutoConnect::_token_NETMASK(PageArgument& args) {
  AC_UNUSED(args);
  return WiFi.subnetMask().toString();
}

String AutoConnect::_token_AP_MAC(PageArgument& args) {
  AC_UNUSED(args);
  uint8_t macAddress[6];
  WiFi.softAPmacAddress(macAddress);
  return AutoConnect::_toMACAddressString(macAddress);
}

String AutoConnect::_token_STA_MAC(PageArgument& args) {
  AC_UNUSED(args);
  uint8_t macAddress[6];
  WiFi.macAddress(macAddress);
  return AutoConnect::_toMACAddressString(macAddress);
}

String AutoConnect::_token_CHANNEL(PageArgument& args) {
  AC_UNUSED(args);
  return String(WiFi.channel());
}

String AutoConnect::_token_DBM(PageArgument& args) {
  AC_UNUSED(args);
  int32_t dBm = WiFi.RSSI();
  return (dBm == 31 ? String(F("N/A")) : String(dBm));
}

String AutoConnect::_token_CPU_FREQ(PageArgument& args) {
  AC_UNUSED(args);
  return String(ESP.getCpuFreqMHz());
}

String AutoConnect::_token_FLASH_SIZE(PageArgument& args) {
  AC_UNUSED(args);
  return String(_getFlashChipRealSize());
}

String AutoConnect::_token_CHIP_ID(PageArgument& args) {
  AC_UNUSED(args);
  return String(_getChipId());
}

String AutoConnect::_token_FREE_HEAP(PageArgument& args) {
  AC_UNUSED(args);
  return String(_freeHeapSize);
}

String AutoConnect::_token_LIST_SSID(PageArgument& args) {
  // Obtain the page number to display.
  // When the display request is the first page, it will be obtained
  // from the scan results of the WiFiScan class if it has already been
  // scanned.
  uint8_t page = 0;
  if (args.hasArg(String(F("page"))))
    page = args.arg("page").toInt();
  else {
    // Scan at a first time
    WiFi.scanDelete();
    _scanCount = WiFi.scanNetworks(false, true);
    AC_DBG("%d network(s) found\n", (int)_scanCount);
  }
  // Preapre SSID list content building buffer
  size_t  bufSize = sizeof('\0') + 192 * (_scanCount > AUTOCONNECT_SSIDPAGEUNIT_LINES ? AUTOCONNECT_SSIDPAGEUNIT_LINES : _scanCount);
  bufSize += 88 * (_scanCount > AUTOCONNECT_SSIDPAGEUNIT_LINES ? (_scanCount > (AUTOCONNECT_SSIDPAGEUNIT_LINES * 2) ? 2 : 1) : 0);
  char* ssidList = (char*)malloc(bufSize);
  if (!ssidList) {
    AC_DBG("ssidList buffer(%d) allocation failed\n", (int)bufSize);
    return _emptyString;
  }
  AC_DBG_DUMB("\n");
  // Locate to the page and build SSD list content.
  static const char _ssidList[] PROGMEM =
    "<input type=\"button\" onClick=\"onFocus(this.getAttribute('value'))\" value=\"%s\">"
    "<label class=\"slist\">%d&#037;&ensp;Ch.%d</label>%s<br>";
  static const char _ssidEnc[] PROGMEM =
    "<span class=\"img-lock\"></span>";
  static const char _ssidPage[] PROGMEM =
    "<button type=\"submit\" name=\"page\" value=\"%d\" formaction=\"/_ac/config\">%s</button>&emsp;";
  _hiddenSSIDCount = 0;
  uint8_t validCount = 0;
  uint8_t dispCount = 0;
  char* slBuf = ssidList;
  *slBuf = '\0';
  for (uint8_t i = 0; i < _scanCount; i++) {
    String ssid = WiFi.SSID(i);
    if (ssid.length() > 0) {
      // An available SSID may be listed.
      // AUTOCONNECT_SSIDPAGEUNIT_LINES determines the number of lines
      // per page in the available SSID list.
      if (validCount >= page * AUTOCONNECT_SSIDPAGEUNIT_LINES && validCount <= (page + 1) * AUTOCONNECT_SSIDPAGEUNIT_LINES - 1) {
        if (++dispCount <= AUTOCONNECT_SSIDPAGEUNIT_LINES) {
          snprintf_P(slBuf, bufSize - (slBuf - ssidList), (PGM_P)_ssidList, ssid.c_str(), AutoConnect::_toWiFiQuality(WiFi.RSSI(i)), WiFi.channel(i), WiFi.encryptionType(i) != ENC_TYPE_NONE ? (PGM_P)_ssidEnc : "");
          slBuf += strlen(slBuf);
        }
      }
      // The validCount counts the found SSIDs that is not the Hidden
      // attribute to determines the next button should be displayed.
      validCount++;
    }
    else
      _hiddenSSIDCount++;
  }
  // Prepare perv. button
  if (page >= 1) {
    snprintf_P(slBuf, bufSize - (slBuf - ssidList), (PGM_P)_ssidPage, page - 1, PSTR("Prev."));
    slBuf = ssidList + strlen(ssidList);
  }
  // Prepare next button
  if (validCount > (page + 1) * AUTOCONNECT_SSIDPAGEUNIT_LINES) {
    snprintf_P(slBuf, bufSize - (slBuf - ssidList), (PGM_P)_ssidPage, page + 1, PSTR("Next"));
  }
  // return ssidList;
  String ssidListStr = String(ssidList);
  free(ssidList);
  return ssidListStr;
}

String AutoConnect::_token_SSID_COUNT(PageArgument& args) {
  AC_UNUSED(args);
  return String(_scanCount);
}

String AutoConnect::_token_HIDDEN_COUNT(PageArgument& args) {
  AC_UNUSED(args);
  return String(_hiddenSSIDCount);
}

String AutoConnect::_token_CONFIG_STAIP(PageArgument& args) {
  AC_UNUSED(args);
  static const char _configIPList[] PROGMEM =
    "<li class=\"exp\">"
    "<label for=\"%s\">%s</label>"
    "<input id=\"%s\" type=\"text\" name=\"%s\" value=\"%s\">"
    "</li>";
  struct _reps {
    PGM_P lid;
    PGM_P lbl;
  } static const reps[]  = {
    { PSTR(AUTOCONNECT_PARAMID_STAIP), PSTR("IP Address") },
    { PSTR(AUTOCONNECT_PARAMID_GTWAY), PSTR("Gateway") },
    { PSTR(AUTOCONNECT_PARAMID_NTMSK), PSTR("Netmask") },
    { PSTR(AUTOCONNECT_PARAMID_DNS1), PSTR("DNS1") },
    { PSTR(AUTOCONNECT_PARAMID_DNS2), PSTR("DNS2") }
  };
  char  liCont[600];
  char* liBuf = liCont;

  for (uint8_t i = 0; i < 5; i++) {
    IPAddress*  ip;
    if (i == 0)
      ip = &_apConfig.staip;
    else if (i == 1)
      ip = &_apConfig.staGateway;
    else if (i == 2)
      ip = &_apConfig.staNetmask;
    else if (i == 3)
      ip = &_apConfig.dns1;
    else if (i == 4)
      ip = &_apConfig.dns2;
    String  ipStr = *ip ? ip->toString() : String(F("0.0.0.0"));
    snprintf_P(liBuf, sizeof(liCont) - (liBuf - liCont), (PGM_P)_configIPList, reps[i].lid, reps[i].lbl, reps[i].lid, reps[i].lid, ipStr.c_str());
    liBuf += strlen(liBuf);
  }
  return String(liCont);
}

String AutoConnect::_token_OPEN_SSID(PageArgument& args) {
  AC_UNUSED(args);
  static const char _ssidList[] PROGMEM = "<input id=\"sb\" type=\"submit\" name=\"%s\" value=\"%s\"><label class=\"slist\">%s</label>%s<br>";
  static const char _ssidRssi[] PROGMEM = "%d&#037;&ensp;Ch.%d";
  static const char _ssidNA[]   PROGMEM = "N/A";
  static const char _ssidLock[] PROGMEM = "<span class=\"img-lock\"></span>";
  static const char _ssidNull[] PROGMEM = "";
  String ssidList;
  station_config_t  entry;
  char  slCont[176];
  char  rssiCont[32];
  AutoConnectCredential credit(_apConfig.boundaryOffset);

  uint8_t creEntries = credit.entries();
  if (creEntries > 0) {
    ssidList = String("");
    _scanCount = WiFi.scanNetworks(false, true);
  }
  else
    ssidList = String(F("<p><b>Geen opgeslagen netwerken gevonden.</b></p>"));

  for (uint8_t i = 0; i < creEntries; i++) {
    rssiCont[0] = '\0';
    PGM_P rssiSym = _ssidNA;
    PGM_P ssidLock = _ssidNull;
    credit.load(i, &entry);
    AC_DBG("A credential #%d loaded\n", (int)i);
    for (int8_t sc = 0; sc < (int8_t)_scanCount; sc++) {
      if (!memcmp(entry.bssid, WiFi.BSSID(sc), sizeof(station_config_t::bssid))) {
        _connectCh = WiFi.channel(sc);
        snprintf_P(rssiCont, sizeof(rssiCont), (PGM_P)_ssidRssi, AutoConnect::_toWiFiQuality(WiFi.RSSI(sc)), _connectCh);
        rssiSym = rssiCont;
        if (WiFi.encryptionType(sc) != ENC_TYPE_NONE)
          ssidLock = _ssidLock;
        break;
      }
    }
    snprintf_P(slCont, sizeof(slCont), (PGM_P)_ssidList, AUTOCONNECT_PARAMID_CRED, reinterpret_cast<char*>(entry.ssid), rssiSym, ssidLock);
    ssidList += String(slCont);
  }
  return ssidList;
}

String AutoConnect::_token_UPTIME(PageArgument& args) {
  AC_UNUSED(args);
  return String(_apConfig.uptime);
}

String AutoConnect::_token_BOOTURI(PageArgument& args) {
  AC_UNUSED(args);
  if (_apConfig.bootUri == AC_ONBOOTURI_ROOT)
    return String(AUTOCONNECT_URI);
  else if (_apConfig.bootUri == AC_ONBOOTURI_HOME)
    return _apConfig.homeUri.length() > 0 ? _apConfig.homeUri : String("/");
  else
    return _emptyString;
}

String AutoConnect::_token_CURRENT_SSID(PageArgument& args) {
  AC_UNUSED(args);
  char  ssid_c[sizeof(station_config_t::ssid) + 1];
  *ssid_c = '\0';
  strncat(ssid_c, reinterpret_cast<char*>(_credential.ssid), sizeof(ssid_c) - 1);
  String  ssid = String(ssid_c);
  return ssid;
}

/**
 *  This function dynamically build up the response pages that conform to
 *  the requested URI. A PageBuilder instance is stored in _rensponsePage
 *  as the response page.
 *  @param  Requested URI.
 *  @retval true  A response page generated.
 *  @retval false Requested uri is not defined.
 */
PageElement* AutoConnect::_setupPage(String uri) {
  PageElement *elm = new PageElement();

  // Restore menu title
  _menuTitle = _apConfig.title;

  // Build the elements of current requested page.
  if (uri == String(AUTOCONNECT_URI)) {

    // Setup /auto
    _freeHeapSize = ESP.getFreeHeap();
    elm->setMold(_PAGE_STAT);
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_INPUT_BUTTON")), std::bind(&AutoConnect::_token_CSS_INPUT_BUTTON, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_ICON_LOCK")), std::bind(&AutoConnect::_token_CSS_ICON_LOCK, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_AUX")), std::bind(&AutoConnect::_token_MENU_AUX, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_CONFIG)) {

    // Setup /auto/config
    elm->setMold(_PAGE_CONFIGNEW);
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_UL")), std::bind(&AutoConnect::_token_CSS_UL, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_ICON_LOCK")), std::bind(&AutoConnect::_token_CSS_ICON_LOCK, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_INPUT_BUTTON")), std::bind(&AutoConnect::_token_CSS_INPUT_BUTTON, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_INPUT_TEXT")), std::bind(&AutoConnect::_token_CSS_INPUT_TEXT, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_AUX")), std::bind(&AutoConnect::_token_MENU_AUX, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("LIST_SSID")), std::bind(&AutoConnect::_token_LIST_SSID, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("SSID_COUNT")), std::bind(&AutoConnect::_token_SSID_COUNT, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("HIDDEN_COUNT")), std::bind(&AutoConnect::_token_HIDDEN_COUNT, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CONFIG_IP")), std::bind(&AutoConnect::_token_CONFIG_STAIP, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_CONNECT)) {

    // Setup /auto/connect
    _menuTitle = FPSTR("Connecting");
    elm->setMold(_PAGE_CONNECTING);
    elm->addToken(String(FPSTR("REQ")), std::bind(&AutoConnect::_induceConnect, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_SPINNER")), std::bind(&AutoConnect::_token_CSS_SPINNER, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CUR_SSID")), std::bind(&AutoConnect::_token_CURRENT_SSID, this, std::placeholders::_1));
 }
  else if (uri == String(AUTOCONNECT_URI_OPEN)) {

    // Setup /auto/open
    elm->setMold(_PAGE_OPENCREDT);
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_ICON_LOCK")), std::bind(&AutoConnect::_token_CSS_ICON_LOCK, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_INPUT_BUTTON")), std::bind(&AutoConnect::_token_CSS_INPUT_BUTTON, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_AUX")), std::bind(&AutoConnect::_token_MENU_AUX, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("OPEN_SSID")), std::bind(&AutoConnect::_token_OPEN_SSID, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_DISCON)) {

    // Setup /auto/disc
    _menuTitle = FPSTR("Disconnect");
    elm->setMold(_PAGE_DISCONN);
    elm->addToken(String(FPSTR("DISCONNECT")), std::bind(&AutoConnect::_induceDisconnect, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_RESET)) {

    // Setup /auto/reset
    elm->setMold(_PAGE_RESETTING);
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("BOOTURI")), std::bind(&AutoConnect::_token_BOOTURI, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("UPTIME")), std::bind(&AutoConnect::_token_UPTIME, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("RESET")), std::bind(&AutoConnect::_induceReset, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_RESULT)) {

    // Setup /auto/result
    elm->setMold("{{RESULT}}");
    elm->addToken(String(FPSTR("RESULT")), std::bind(&AutoConnect::_invokeResult, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_SUCCESS)) {

    // Setup /auto/success
    elm->setMold(_PAGE_SUCCESS);
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_TABLE")), std::bind(&AutoConnect::_token_CSS_TABLE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_AUX")), std::bind(&AutoConnect::_token_MENU_AUX, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("ESTAB_SSID")), std::bind(&AutoConnect::_token_ESTAB_SSID, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("WIFI_MODE")), std::bind(&AutoConnect::_token_WIFI_MODE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("WIFI_STATUS")), std::bind(&AutoConnect::_token_WIFI_STATUS, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("LOCAL_IP")), std::bind(&AutoConnect::_token_LOCAL_IP, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("GATEWAY")), std::bind(&AutoConnect::_token_GATEWAY, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("NETMASK")), std::bind(&AutoConnect::_token_NETMASK, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CHANNEL")), std::bind(&AutoConnect::_token_CHANNEL, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("DBM")), std::bind(&AutoConnect::_token_DBM, this, std::placeholders::_1));
  }
  else if (uri == String(AUTOCONNECT_URI_FAIL)) {

    // Setup /auto/fail
    _menuTitle = FPSTR("Failed");
    elm->setMold(_PAGE_FAIL);
    elm->addToken(String(FPSTR("HEAD")), std::bind(&AutoConnect::_token_HEAD, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_BASE")), std::bind(&AutoConnect::_token_CSS_BASE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_TABLE")), std::bind(&AutoConnect::_token_CSS_TABLE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("CSS_LUXBAR")), std::bind(&AutoConnect::_token_CSS_LUXBAR, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_PRE")), std::bind(&AutoConnect::_token_MENU_PRE, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_AUX")), std::bind(&AutoConnect::_token_MENU_AUX, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("MENU_POST")), std::bind(&AutoConnect::_token_MENU_POST, this, std::placeholders::_1));
    elm->addToken(String(FPSTR("STATION_STATUS")), std::bind(&AutoConnect::_token_STATION_STATUS, this, std::placeholders::_1));
  }
  else {
    delete elm;
    elm = nullptr;
  }

  // Restore the page transfer mode and the content build buffer
  // reserved size corresponding to each URI defined in structure
  // _pageBuildMode.
  if (elm) {
    for (uint8_t n = 0; n < sizeof(_pageBuildMode) / sizeof(PageTranserModeST); n++)
      if (!strcmp(_pageBuildMode[n].uri, uri.c_str())) {
        _responsePage->reserve(_pageBuildMode[n].rSize);
        _responsePage->chunked(_pageBuildMode[n].transMode);
        break;
      }
  }

  return elm;
}

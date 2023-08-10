# MUD_practice

help查看指令

        LPC語言是C語言的延伸，因應遊戲的特性融合了許多語言的特性，最大的差異是必須透過driver做直譯器來執行，執行後透過設定檔來載入配置的文件master.c、simul_efun.c，並等待玩家連線
1. 玩家註冊登入系統
        伺服器啟用後等待玩家連線，玩家連線後driver自動調用master傳回連接對象，之後調用login.c中的logon()，再設置完連線對象的ip後，調用常駐程式展示歡迎頁面並指示玩家現該如何輸出，過程中將玩家的輸入去資料庫檢測，因應結果來做應對，若資料不存在便啟動註冊流程，資料分成帳密以及角色資料來做儲存。
2. 人物指令系統
        人物所輸入的指令由常駐程式daemons/commands來接收，並因應儲存在cmds資料夾底下的指令來運作，每個對象依據權限、所處環境會擁有不同的指令能用。
3. 人物聊天頻道系統
say + “message”: 對當前環境的玩家講話
shout: 對遊戲中所有活著的玩家講話
4. 房間地圖系統
inherit/room.c繼承mudcore裡房間的模板，std/room.c設定了幾種標準情況，之後設定初始房間start_room，每次移動完會調用look_room，展示當前環境的狀況，也能透過look指令直接看NPC或怪物。
5. 道具物品系統
inherit/item.c繼承mudcore裡物品的模板，std/item.c準備了不同種物品的情況，之後再依據後續需求設定物品。
6. 怪物系統
怪物擁有自己的屬性，會記錄在常駐程式monster_d.c，透過給予不同的參數能迅速生出不同種類與等級的怪，在此地圖上隨機不同數目的怪物，使用fight/f + (monster name)能與之自動戰鬥。
7. 戰鬥系統
將心跳系統綁定在用戶上，每隔一段時間會檢查是否有攻擊目標，若有則開始攻擊，搭配使用fight/f指令選擇目標後，將其加入至攻擊目標，便會隨時間戰鬥，戰鬥採用最簡單的每次互相攻擊，若一方hp歸零則將其消滅


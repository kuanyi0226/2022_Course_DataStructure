# HW2 Mazing Problem 
# 主要架構及函式

## 一、主要架構
1. 定義迷宮大小: mazeRow, mazeCol 皆為17
2. 建立struct offsets: 為走不同方向時，當前點所需移動的變量
(a為row的變量、b為column的變量)

3. 依照題目Fig.1，建立九個方向(index從0~8，實際走迷宮時，不會用到0-原點)
(0)原點(O)、(1)東(E)、(2)東南(SE)、(3)南(S)、(4)西南(SW)、
(5)西(W)、(6)西北(NW)、(7)北(N)、(8)東北(NE)

4. 建立struct Items: 放到Stack中記錄目前走過的路徑。
每一個Items記錄一個square的座標x(rol),y(col)，
以及如果上一個Items遇到死路被Pop時，輪到自己時，要走哪個方向
包含有參數建構子(初始化Items)及無參數建構子(用於初始化Stack中的Items array)

5. 建立class Stack: 記錄目前走過的路徑，在程式末端詳細定義。
(1) members:
(a) stack: 一個Items array 用來記錄目前走過的路徑
(b) top: 目前走到的位置(從A點走向B點時，確定B點可以到達，才會將A點push進stack)
(c) stackCapcity: stack容量為迷宮大小

(2)methods: 最基本的Stack methods
(建構子、判斷為空?、取得Top、Push、Pop)

6. 宣告一個offsets array(moveDir)，在main()中詳細定義每個方向的不同移動變量
7. 用2D Array建立原始迷宮(maze)、記錄走過哪些點(mark)

8. 宣告Path函式，傳入迷宮的maxRow,maxCol，在函式中就會開始尋找maze的可能出路

9. 宣告printStep函式，使用於Path中，傳入目前第幾步、位置(row,col)後，
同時印出該步index及position在console window和output.txt中，以符合題目要求


## 二、Functions used
1. main:
(1) 詳細定義moveDir每一個方向(原點、東、東南......)要移動的變量
(2) 讀取一個迷宮輸入檔，一個一個數字存入maze array中，完成原始迷宮初始化
(3) 呼叫Path，輸入迷宮大小mazeRow, mazeCol，找到可能的路徑，並印出結果

2. Path:
(1) 設立一個計數器，計算總共走了幾步
(2) 初始化stack，從(1,0)開始走。使用temp記錄一個temp Items
(3) 進入第一層while，正式開始尋找路徑; 一旦離開，即搜尋完畢。
使用變數i, j, d記錄目前位置以及選擇的方向

(4) 進入第二層while，開始一直往前走 
(a) 使用g,h變數，記錄對於目前這個點(以及其選擇的方向)，下一個點的座標
(b) 如果g, h是迷宮終點(15,16)，印出倒數兩步，成功找到一條出路，離開Path
(c) 如果是可走的點&還沒走過的點，此點mark為1(即走過了)，將目前位置(i, j)以及遇到死路時，
Pop()掉Top後，回到i, j時，嘗試下一個方向(d+1)(注意d或d+1的範圍是1~8)，存入temp中並Push進stack並印出其位置。
將目前位置改為g, h，方向預設成E；

如果不是可走的點or走過的點，d++，嘗試下一個方向。若已試過每一個方向，遇到死路時，印出遇到死路當下的點，
跳出第二層while，使用Pop開始走回頭路，直到找到可以繼續往前的位置

(d)若一直Pop()回到原點，stack為空時，代表沒有出路，逃脫失敗，離開Path


3. printStep: 
傳入某步的index(counter)以及位置後，同時印在console window及output.txt上。
若是第一筆資料，需先清空output檔，其餘資料慢慢追加在其後。

4. 詳細定義Stack的基本methods，即最普通、常見的stack methods定義方式
(1)建構子: 傳入迷宮array大小，初始化stack array；top設為-1
(2)IsEmpty: 判斷stack array是否為空
(3)Top: 回傳一個Top Items
(4)Push: 傳入一個Items，push進stack array中
(5)Pop: top往下一格(等同於去除最頂端的Items)






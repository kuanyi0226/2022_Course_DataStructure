HW4 Prim & Dijkstra Algo

一、兩個cpp檔案共同的架構
1. findMinVer(vector<int>, vector<bool>, int): 
傳入一個vector<int> distance, 一個vector<bool> visited, int 總共vertices數量，
會回傳distance中還沒被visited且最小的distance index 
協助兩個檔案各自的Algo Function 找 MST & shortest path

2. Algo Function: 分別為 Prim(...) & Dijkstra(...)，傳入關於Graph的參數，
並將運算的結果copy回main()，詳細參數、定義於後方說明

3. main(): 
(1) 初始化26*26陣列(adjacent matrix)，以及一些Graph相關變數
(2) 清空out file
(3) 讀取想要打開的input file
(4) 將input file中的data掃描到26*26的相鄰矩陣中形成Graph，並找出此Graph的vertices數量
ps. a~z讀進來時分別對應到(index 0~25)
(5) 建立一個用來存取運算結果的vector(接收Algo Function運算結果)
(6) 把Graph傳入各自的Algo Function運算找出MST & Shortest Path
(7) 根據題目要求(ascending)，印出結果(把index 0~25 轉回 a~z)


二、 prim.cpp
1. 有定義一個struct Edge用來存放Prim運算完後，連接vertices的每一個邊
(包含edge的兩個頂點、weight)

2. Prim Algo
(1) 傳入26*26相鄰矩陣(graph)、int 總頂點數、 int起始頂點、vector<Edge>接收Prim運算結果(MST)
(2) 將graph轉換成 總頂點數*總頂點數的相鄰矩陣(adjMatrix)方便之後操作
(3) 建立三個序列分別用來存取各個頂點在運算時的distance(一開始都是無限大), 是否被visited,parent是誰
(4) 開始找MST: 
每一輪中，使用findMinVer，找到還沒被visited且distance最短的(weight最小)vertex去visit它，
再根據visit到的那個vertex之所有相鄰邊，去更新distance vector是否各頂點的distance有更小值。
以此循環找到MST
(5)根據parent、題目要求(字母output也要小到大)，
把adjMatrix的MST資料，打包成一條條Edge回去main()印出來。


三、dijkstra.cpp(基本上類似於prim)
Dijkstra Algo:
(1) 傳入26*26相鄰矩陣(graph)、int 總頂點數、 int起始頂點、vector<int>接收Dijkstra運算結果(shortest path)
(2) 將graph轉換成 總頂點數*總頂點數的相鄰矩陣(adjMatrix)方便之後操作
(3) 建立兩個序列分別用來存取各個頂點在運算時的distance(一開始都是無限大), 是否被visited
(4) 開始找起始點到各點shortest path: 
每一輪中，使用findMinVer，找到還沒被visited且distance最短的vertex去visit它，
如果visit的點具有相鄰邊可抵達其他點 且經visit的點繞路到該點的距離小於原本的，就更新該點distance。
以此循環找到起始點到各點shortest path
(5) 將結果複製回main()中的vector<int>shortest，印出結果



DS HW3 BST

一、前置作業
1. print相關函式定義: 方便我只要呼叫一次函式，就能將傳入的string or int值印到Console及output.txt中(包含換行及不換行)
詳細定義在main function底下說明。

2. 宣告/定義 BST所需用到的class, structure, functions(使用linked list的方式implement BST)
(1) struct node: BST的節點，data即節點的數字大小，其有左右子節點
(2) BST class: 有一個最頂端的root，也有許多methods來完成題目要求的operations，詳細定義在main function底下說明。
(3) 節點相關操作functions
	(a) createNode(int): 傳入想要插入的數字量值，並創造一個node，其data為傳入值，左右子節點預設成NULL。
	(b) findSuccessor(node*): 傳入某節點*，找到其successor的值
	(c) findPredecessor(node*): 傳入某節點*，找到其predecessor的值
(4) Queue class: 根據題目要求，用於BST中，協助實現printlevelorder()，裡面的members只宣告本次題目會用到的Queue members。
    且Queue以vector實作(每個element 都是 node*)，故沒有要求傳入size


二、main() 包含:
1. 一些變數的前置宣告(BST實例...等)
2. 選擇檔案: 讓使用者在console打入想要開啟的檔案，並輸入檔案名稱到output.txt
3. 開始打開輸入檔，掃描並執行要求的operations，在while迴圈中不斷執行
(a) printQuestions()印出詢問使用者要使用的指令
(b) 讀取operation
(c) 若operation是 E ，中止迴圈
(d) 若operation是 I, D, S，則讀取一行數字到numbers中(type is vector<int>)

//執行操作指令
(e) 若operation是 I，將下一行的每個數字，都去create一個node，並insert到bst(type is BST)中。
(f) 若operation是 D，將下一行的每個數字，都先去search一次有沒有在樹中；若有，從bst中將其delete。
(g) 若operation是 S，將下一行的每個數字，去search一次有沒有在樹中。
(h) 若operation是 P，則分別執行bst的print-preorder(), inorder(), postorder(), levelorder()。

4. 關閉輸入檔，結束程式


三、函式的詳細定義
1. print相關函式: 會打開、關閉output.txt。根據傳入的參數(string or int)分別印到console和txt中
2. printQuestions(): 印出詢問使用者要選擇使用的指令(5種)

//BST method: 會判斷root是否為空
3. insert(node*): 傳入一個node*，將其根據BST的規定，insert到樹中
4. delete_node(node*, int): 傳入一個node及目標刪除數字，用recursive的方式，搭配先前定義的findSuccessor(node*), findPredecessor(node*)
完成題目要求刪除node的不同情況，並return刪掉的節點
5. search(int): 傳入一個目標搜尋數字，用迴圈的方式往下找，並回傳搜尋結果(node*)
6. print 4 orders: 前三種order，函式各自有driver和workhorse，用recursive的方式，印出所求
(註: level order是根據題目要求，使用Queue，搭配while迴圈)

//Queue class methods:
7. Queue(): constructor for Queue
8. isEmpty()
9. Add(node*): 傳入一個node*加到queue隊伍後面
10. Delete(): 刪除並回傳queue隊伍最前面的node*
 
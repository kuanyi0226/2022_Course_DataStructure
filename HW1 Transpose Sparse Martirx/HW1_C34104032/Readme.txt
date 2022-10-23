主要文件說明

一、輸入輸出文件
1. p1.in:
裡面包含了要輸入的測資，第一行分別是array的rows和columns數，
第二行開始是利用triple format表示的non-zero element(row-col-value)。

2. p2.out:
Output data要輸出到此檔案中，先輸出其中一題transpose的結果，再輸出兩小題分別transpose時所耗的時間(單位:秒)


二、前置文件(Class)
1. MatrixTerm.h & MatrixTerm.cpp:
用來寫MatrixTerm 這個class，private members分別用來記錄每一個MatrixTerm所在的row & column，以及它的value。
有兩個pulic method，分別是用來修改、取得MatrixTerm Object的private members。

2. SparseMatrix.h & SparseMatrix.cpp:
用來寫SparseMatrix 這個class，private members分別用來記錄每一個SparseMatrix物件的rows, columns, terms數量，
以及一個存放它所有MatrixTerm的smArray(指標)。
public methods則是有:
(1)Constructor: 初始化SparseMatrix物件(傳入rows,cols,terms)
(2)setArray: 負責將main.cpp讀取到的輸入資料(MatrixTerm型別)，傳入原始(尚未transposed)SparseMatrix中的smArray中，完成初始化。
(3)tradiTranspose: 負責第一小題(2D Array 傳統處理轉置矩陣的方法)。先創造一個用來表示已經transposed過的SparseMatrix b，
接著利用原始SparseMatrix中的non-zero element資料去建構一個2D array，並宣告一個temp 2D Array(transResult)用來暫存原始2D array轉置過的結果。
接下來便能開始進行轉置過程: 直接將原始2D array中所有element的row, column顛倒，將值傳入到transResult Array中(即最傳統轉置矩陣的方法)，
最後將transResult Array中"non-zero"的elements存入b.smArray中並回傳一個SparseMatrix b。
(4)Transpose: 負責第二小題(使用課本上的轉置方法)，一樣先創造一個用來表示已經transposed過的SparseMatrix b，接者宣告currentB紀錄b中smArray的index，
以及b.smArray中的變數。接著便開始轉置，掃描一個個column，並掃描所有原始矩陣的terms(find elements in column c)，如果有smArray中的col對應到目前column的，
就將b的這個term的row設成c、剩下的原始資料也抄過去term的col & value，以此重複完成轉置並回傳一個SparseMatrix b。
(5)printResult: 將第一題轉置後回傳的SparseMatrix b傳進來，印出Output要求印出的東西到p1.out中。

三、main.cpp
1. Timing Function(printTransTime):用來記錄兩次transpose過程的時間。
首先先宣告一個Function及Timing所需的變數，並在main.cpp的最後定義它: 由於轉置時間太短了，故我使用的是<Windows.h>的高精度計時器，
先用QueryPerformanceFrequency去記下CPU的頻率，再分別利用開始及結束的QueryPerformanceCounter，找時間差值，
最後將兩種轉置方法的差值和頻率分別輸入進這個函式中，找出兩者的轉置時間。

2. 讀取p1.in並初始化原始SparseMatrix:
(1)打開p1.in檔案
(2)讀取rows,cols,terms去建立原始SparseMatrix
(3)關閉p1.in
(4)再次打開p1.in
(5)將每一行non-zero的數據讀入一個個暫時的MatrixTerm物件中，並將不同index的MatrixTerm傳入原始矩陣的smArray中。
(6)關閉p1.in

3.輸出資料到p1.out:
(1)sm.printResult(sm.tradiTranspose()); -----印出第一小題的轉置結果到p1.out中。
在兩小題的transpose過程前後添加一個Counter，呼叫printTransTime Function，傳入計時相關係數，並印出兩種轉置方法分別的時間到p1.out中。


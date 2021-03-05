@chcp 866>nul 
@<"C:\Users\kuzme\Desktop\cr\wifies-win1251.txt">"C:\Users\kuzme\Desktop\cr\wifies-UTF8.txt" (for /f "delims=" %%i in ('find/n /v ""') do @chcp 65001>nul& set x=%%i& cmd/v/c echo[!x:*]^^=!)

@echo off  
:ac  
  
rand>in.txt  :出数据  
A<in.txt>me.txt    :被测程序  
shi<in.txt>out.txt   :暴力程序  
fc me.txt out.txt  
:diff -q me.txt out.txt 这句可以代替上一句  
if errorlevel=1 goto wa       
echo ac  
goto ac  
  
:wa  
echo wa  
:type me.txt out.txt :这句可有可无  
pause  
  
退出状态  
　　此命令返回下列退出值：  
　　0 未找到不同处。  
　　1 找到不同处。  
　　>1 发生错误。 
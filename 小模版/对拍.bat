@echo off  
:ac  
  
rand>in.txt  :������  
A<in.txt>me.txt    :�������  
shi<in.txt>out.txt   :��������  
fc me.txt out.txt  
:diff -q me.txt out.txt �����Դ�����һ��  
if errorlevel=1 goto wa       
echo ac  
goto ac  
  
:wa  
echo wa  
:type me.txt out.txt :�����п���  
pause  
  
�˳�״̬  
����������������˳�ֵ��  
����0 δ�ҵ���ͬ����  
����1 �ҵ���ͬ����  
����>1 �������� 
import java.util.*;

import java.io.*;

public class Main 

{
	public Bool check(String s,int t){
		for(int i=0;i<s.length();i++)
			if(s[i]!=s[i%t])
				return false;
		return true;
	}
	public static void main(String[] args)

	{
	
		Scanner cin = new Scanner(System.in);
		int T=cin.nextInt();
		while(T--){
			String s=cin.next();
			int t=0;
			while((!check(t))&&(t<s.length()))t++;
		}
		
	}

}
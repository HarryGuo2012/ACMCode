#include <windows.h>

int main(){
	system("netsh wlan set hostednetwork mode=allow ssid=hahahaha key=frogfrogfrog");
	system("netsh wlan start hostednetwork");
	return 0;
}
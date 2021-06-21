#include <iostream>

int main() {
	int n, m, tmp, bit=1, arr[100][100];
	scanf("%d %d", &n, &m);

	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d", &arr[i][j]);

while(bit){
	for(int i=0;i<n;i++){
		tmp=0;
		for(int j=0;j<m;j++)
			tmp+=arr[i][j];
		if(tmp<0){
			for(int j=0;j<m;j++)
				arr[i][j]=-arr[i][j];
			printf("l %d\n", i);
			}
	}
	for(int i=0;i<m;i++){
		tmp=0;
		for(int j=0;j<n;j++)
			tmp+=arr[j][i];
		if(tmp<0){
			for(int j=0;j<n;j++)
				arr[j][i]=-arr[j][i];
			printf("c %d\n", i);
			}
	}
	bit=0;
	for(int i=0;i<n;i++){
		tmp=0;
		for(int j=0;j<m;j++)
			tmp+=arr[i][j];
		if(tmp<0){
			bit=1;
			break;
		}
	}
	if(!bit)
		for(int i=0;i<m;i++){
			tmp=0;
			for(int j=0;j<n;j++)
				tmp+=arr[j][i];
			if(tmp<0){
				bit=1;
				break;
			}
		}
	}
	return 0;
}

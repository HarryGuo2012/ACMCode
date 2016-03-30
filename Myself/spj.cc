/*
 * cdoj, UESTC ACMICPC Online Judge
 * Copyright (c) 2012  fish <@link lyhypacm@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
 using namespace std;

#define WA 0
#define AC 1
#define PE 2
#define SE 3
const double EPS=1e-6;

/**
 * @brief
 *    Basic judge item for judger, store stdard input and output, user output
 *  FILE* entity.
 */
struct Node {
  FILE* data_input;
  FILE* data_output;
  FILE* user_output;
};

static Node* node_pointer;

/**
 * @brief
 *    if statement is not true, print exit_code's string and exit SPJ
 */
void dump(bool statement, const int& exit_code) {
  if (statement)
    return;
  if (node_pointer->data_input != NULL)
    fclose(node_pointer->data_input);
  if (node_pointer->data_output != NULL)
    fclose(node_pointer->data_output);
  if (node_pointer->user_output != NULL)
    fclose(node_pointer->user_output);
  if (exit_code == WA)
    puts("WA");
  else if (exit_code == AC)
    puts("AC");
  else if (exit_code == PE)
    puts("PE");
  else
    puts("SE");
  delete node_pointer;
  exit(0);
}

int nextInt(FILE* fp) {
  int variable;
  dump(fscanf(fp, "%d", &variable) == 1, fp == stdin ? WA : SE);
  return variable;
}

long long nextLong(FILE* fp) {
  long long variable;
  dump(fscanf(fp, "%lld", &variable) == 1, fp == stdin ? WA : SE);
  return variable;
}

double nextDouble(FILE* fp) {
  double variable;
  dump(fscanf(fp, "%lf", &variable) == 1, fp == stdin ? WA : SE);
  return variable;
}

void nextString(FILE* fp, char* buf) {
  dump(fscanf(fp, "%s", buf) == 1, fp == stdin ? WA : SE);
}

int sgn(double variable) {
  return variable < -EPS ? -1 : variable > EPS;
}

int compare(double lhs, double rhs) {
  return sgn(lhs - rhs);
}

/**
 * @brief
 *    Judge for specific problem, only function needed to modify.
 * @author RuinsHe<lyhypacm@gmail.com>
 */
 #define MAX_N 555
 #define INF MAX_N*MAX_N+1
int N,K;
int d[MAX_N][MAX_N];
char buff[MAX_N];

vector<int> road;
bool vis[MAX_N];

void floyd(){
  for(int k=0;k<N;k++)
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}

void judge() {
  N=nextInt(node_pointer->data_input);
  K=nextInt(node_pointer->data_input);
  for(int i=0;i<N;i++){
    nextString(node_pointer->data_input,buff);
    for(int j=0;j<N;j++){
      if(buff[j]=='1')
        d[i][j]=1;
      else
        d[i][j]=INF;
    }
  }
  for(int i=0;i<N;i++)
    d[i][i]=0;
  floyd();
  for(int i=0;i<N;i++){
    int a=nextInt(node_pointer->user_output);
    if(a<=0||a>N)dump(false,WA);
    a--;
    if(vis[a])dump(false,WA);
    vis[a]=1;
    road.push_back(a);
  }
  for(int i=1;i<N;i++)
    if(d[road[i-1]][road[i]]>K)dump(false,WA);
}

int main(int argc, char* argv[]) {
  node_pointer = new Node();
  dump(argc >= 3, SE);
  node_pointer->data_input = fopen(argv[1], "r");
  dump(node_pointer->data_input != NULL, SE);
  node_pointer->data_output = fopen(argv[2], "r");
  dump(node_pointer->data_output != NULL, SE);
  node_pointer->user_output = stdin;
  dump(node_pointer->user_output != NULL, SE);
  judge();
  dump(false, AC);
  return 0;
}
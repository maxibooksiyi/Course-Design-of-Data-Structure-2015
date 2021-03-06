#include<stdio.h>
#include<malloc.h>
#include<math.h>
typedef struct Polynomial{
 float coef;
 int expn;
 struct Polynomial *next;
}*Polyn,Polynomial;               //Polyn为结点指针类型
void Insert(Polyn p,Polyn h){     
 if(p->coef==0) free(p);       //系数为0的话释放结点
 else{
  Polyn q1,q2;
  q1=h;q2=h->next;
  while(q2&&p->expn>q2->expn){   //查找插入位置
   q1=q2;
   q2=q2->next;
  }
  if(q2&&p->expn==q2->expn){     //将指数相同相合并
   q2->coef+=p->coef;
   free(p);
   if(!q2->coef){             //系数为0的话释放结点
    q1->next=q2->next;
    free(q2);
   }
  }
  else{                          //指数为新时将结点插入
   p->next=q2;
   q1->next=p;
  }
 }
}//Insert
Polyn CreatePolyn(Polyn head,int m){//建立一个头指针为head、项数为m的一元多项式
 int i;
 Polyn p;
 p=head=(Polyn)malloc(sizeof(struct Polynomial));
 head->next=NULL;
 for(i=0;i<m;i++){
  p=(Polyn)malloc(sizeof(struct Polynomial));//建立新结点以接收数据
  printf("请输入第%d项的系数与指数:",i+1);
  scanf("%f %d",&p->coef,&p->expn);
  Insert(p,head);   //调用Insert函数插入结点
 }
 return head;
}//CreatePolyn
void DestroyPolyn(Polyn p){//销毁多项式p
 Polyn q1,q2;
 q1=p->next;
 q2=q1->next;
 while(q1->next){
  free(q1);
  q1=q2;//指针后移
  q2=q2->next;
 }
}
void PrintPolyn(Polyn P){ 
 Polyn q=P->next; 
 int flag=1;//项数计数器
 if(!q) { //若多项式为空，输出0
  putchar('0'); 
  printf("\n");
  return;
 }   
 while (q){
  if(q->coef>0&&flag!=1) putchar('+'); //系数大于0且不是第一项
  if(q->coef!=1&&q->coef!=-1){//系数非1或-1的普通情况
   printf("%g",q->coef); 
   if(q->expn==1) putchar('X');
   else if(q->expn) printf("X^%d",q->expn);
  }
  else{
   if(q->coef==1){
    if(!q->expn) putchar('1'); 
    else if(q->expn==1) putchar('X'); 
    else printf("X^%d",q->expn);
   }
   if(q->coef==-1){
    if(!q->expn) printf("-1"); 
    else if(q->expn==1) printf("-X"); 
    else printf("-X^%d",q->expn);
   }
  }
  q=q->next; 
  flag++;
 }//while
 printf("\n");
}//PrintPolyn
int compare(Polyn a,Polyn b){
 if(a&&b){
  if(!b||a->expn>b->expn) return 1;
  else if(!a||a->expn<b->expn) return -1;
  else return 0;
 }
 else if(!a&&b) return -1;//a多项式已空，但b多项式非空
 else return 1;//b多项式已空，但a多项式非空
}//compare
Polyn AddPolyn(Polyn pa,Polyn pb){//求解并建立多项式a+b，返回其头指针
 Polyn qa=pa->next;
 Polyn qb=pb->next;
 Polyn headc,hc,qc;
 hc=(Polyn)malloc(sizeof(struct Polynomial));//建立头结点
 hc->next=NULL;
 headc=hc;
 while(qa||qb){
  qc=(Polyn)malloc(sizeof(struct Polynomial));
  switch(compare(qa,qb)){
  case 1:
   {
   qc->coef=qa->coef;
   qc->expn=qa->expn;
   qa=qa->next;
   break;
   }
  case 0:
   { 
   qc->coef=qa->coef+qb->coef;
   qc->expn=qa->expn;
   qa=qa->next;
   qb=qb->next;
   break;
   }
  case -1:
   {
   qc->coef=qb->coef;
   qc->expn=qb->expn;
   qb=qb->next;
   break;
   } 
  }//switch
  if(qc->coef!=0){
   qc->next=hc->next;
   hc->next=qc;
   hc=qc;
  }
  else free(qc);//当相加系数为0时，释放该结点
 }//while
 return headc;
}//AddPolyn
Polyn SubtractPolyn(Polyn pa,Polyn pb){//求解并建立多项式a+b，返回其头指针
 Polyn h=pb;
 Polyn p=pb->next;
 Polyn pd;
 while(p){           //将pb的系数取反
  p->coef*=-1;
  p=p->next;
 }
 pd=AddPolyn(pa,h);
 for(p=h->next;p;p=p->next)    //恢复pb的系数
  p->coef*=-1;
 return pd;
}//SubtractPolyn
int main(){
 int m,n,flag=0,Z=0,t,j,g,i,f=1,h,u=0;
 //float x;
 Polyn pa=0,pb=0,pc,pd,pe,pf;//定义各式的头指针，pa与pb在使用前付初值NULL
 printf("请输入a的项数:");
 scanf("%d",&m);
 pa=CreatePolyn(pa,m);//建立多项式a
 printf("请输入b的项数:");
 scanf("%d",&n);
 pb=CreatePolyn(pb,n);//建立多项式a
 //输出菜单
 printf("**********************************************\n");
 printf("操作提示：\n\t1.输出多项式a和b\n\t2.建立多项式a+b\n\t3.建立多项式a-b\n\t5.输入X0，求出多项式a的值\n");
 printf("\t4.退出\n**********************************************\n");
 for(;;flag=0){
  printf("执行操作：");
  scanf("%d",&flag);
  if(flag==1){
   printf("多项式a：");PrintPolyn(pa);
   printf("多项式b：");PrintPolyn(pb);continue;
  }
  if(flag==2){
   pc=AddPolyn(pa,pb);
   printf("多项式a+b：");PrintPolyn(pc);
   DestroyPolyn(pc);continue;
  }
  if(flag==3){
   pd=SubtractPolyn(pa,pb);
   printf("多项式a-b：");PrintPolyn(pd);
   DestroyPolyn(pd);continue;
  }
  if(flag==4) break;
  if(flag==5){
	  scanf("%d",&t);
	  Z=0;
	 // Z=Z+431602080;//为什么会这样子431602080到底是哪里来的。
    pa=pa->next;//加了这一条之后终于没有那个说明431602080，说明最开始有些地方是没有值的。
  while(pa!=NULL)
	  //while(u==2)

  {
	  //h=(int)pa->coef;
	  h=ceil(pa->coef);//float转int
  j=pa->expn;
  f=1;
  for(i=0;i<j;i++)
  {
	  f=f*t;
  }
  g=h*f;
  //Y=Y+g;
  Z+=g;
  printf("%d\n",g);
  printf("%d\n",Z);
  pa=pa->next;
  }
	 // Y=Y/100000;
  //printf("%d",Y);
  continue;}


  if(flag<1||flag>4) printf("Error!!!\n");continue;
  
 }//for
 DestroyPolyn(pa);
 DestroyPolyn(pb);
 return 0;
}


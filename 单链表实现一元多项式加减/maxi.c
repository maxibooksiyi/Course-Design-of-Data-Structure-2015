#include<stdio.h>
#include<malloc.h>
#include<math.h>
typedef struct Polynomial{
 float coef;
 int expn;
 struct Polynomial *next;
}*Polyn,Polynomial;               //PolynΪ���ָ������
void Insert(Polyn p,Polyn h){     
 if(p->coef==0) free(p);       //ϵ��Ϊ0�Ļ��ͷŽ��
 else{
  Polyn q1,q2;
  q1=h;q2=h->next;
  while(q2&&p->expn>q2->expn){   //���Ҳ���λ��
   q1=q2;
   q2=q2->next;
  }
  if(q2&&p->expn==q2->expn){     //��ָ����ͬ��ϲ�
   q2->coef+=p->coef;
   free(p);
   if(!q2->coef){             //ϵ��Ϊ0�Ļ��ͷŽ��
    q1->next=q2->next;
    free(q2);
   }
  }
  else{                          //ָ��Ϊ��ʱ��������
   p->next=q2;
   q1->next=p;
  }
 }
}//Insert
Polyn CreatePolyn(Polyn head,int m){//����һ��ͷָ��Ϊhead������Ϊm��һԪ����ʽ
 int i;
 Polyn p;
 p=head=(Polyn)malloc(sizeof(struct Polynomial));
 head->next=NULL;
 for(i=0;i<m;i++){
  p=(Polyn)malloc(sizeof(struct Polynomial));//�����½���Խ�������
  printf("�������%d���ϵ����ָ��:",i+1);
  scanf("%f %d",&p->coef,&p->expn);
  Insert(p,head);   //����Insert����������
 }
 return head;
}//CreatePolyn
void DestroyPolyn(Polyn p){//���ٶ���ʽp
 Polyn q1,q2;
 q1=p->next;
 q2=q1->next;
 while(q1->next){
  free(q1);
  q1=q2;//ָ�����
  q2=q2->next;
 }
}
void PrintPolyn(Polyn P){ 
 Polyn q=P->next; 
 int flag=1;//����������
 if(!q) { //������ʽΪ�գ����0
  putchar('0'); 
  printf("\n");
  return;
 }   
 while (q){
  if(q->coef>0&&flag!=1) putchar('+'); //ϵ������0�Ҳ��ǵ�һ��
  if(q->coef!=1&&q->coef!=-1){//ϵ����1��-1����ͨ���
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
 else if(!a&&b) return -1;//a����ʽ�ѿգ���b����ʽ�ǿ�
 else return 1;//b����ʽ�ѿգ���a����ʽ�ǿ�
}//compare
Polyn AddPolyn(Polyn pa,Polyn pb){//��Ⲣ��������ʽa+b��������ͷָ��
 Polyn qa=pa->next;
 Polyn qb=pb->next;
 Polyn headc,hc,qc;
 hc=(Polyn)malloc(sizeof(struct Polynomial));//����ͷ���
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
  else free(qc);//�����ϵ��Ϊ0ʱ���ͷŸý��
 }//while
 return headc;
}//AddPolyn
Polyn SubtractPolyn(Polyn pa,Polyn pb){//��Ⲣ��������ʽa+b��������ͷָ��
 Polyn h=pb;
 Polyn p=pb->next;
 Polyn pd;
 while(p){           //��pb��ϵ��ȡ��
  p->coef*=-1;
  p=p->next;
 }
 pd=AddPolyn(pa,h);
 for(p=h->next;p;p=p->next)    //�ָ�pb��ϵ��
  p->coef*=-1;
 return pd;
}//SubtractPolyn
int main(){
 int m,n,flag=0,Z=0,t,j,g,i,f=1,h,u=0;
 //float x;
 Polyn pa=0,pb=0,pc,pd,pe,pf;//�����ʽ��ͷָ�룬pa��pb��ʹ��ǰ����ֵNULL
 printf("������a������:");
 scanf("%d",&m);
 pa=CreatePolyn(pa,m);//��������ʽa
 printf("������b������:");
 scanf("%d",&n);
 pb=CreatePolyn(pb,n);//��������ʽa
 //����˵�
 printf("**********************************************\n");
 printf("������ʾ��\n\t1.�������ʽa��b\n\t2.��������ʽa+b\n\t3.��������ʽa-b\n\t5.����X0���������ʽa��ֵ\n");
 printf("\t4.�˳�\n**********************************************\n");
 for(;;flag=0){
  printf("ִ�в�����");
  scanf("%d",&flag);
  if(flag==1){
   printf("����ʽa��");PrintPolyn(pa);
   printf("����ʽb��");PrintPolyn(pb);continue;
  }
  if(flag==2){
   pc=AddPolyn(pa,pb);
   printf("����ʽa+b��");PrintPolyn(pc);
   DestroyPolyn(pc);continue;
  }
  if(flag==3){
   pd=SubtractPolyn(pa,pb);
   printf("����ʽa-b��");PrintPolyn(pd);
   DestroyPolyn(pd);continue;
  }
  if(flag==4) break;
  if(flag==5){
	  scanf("%d",&t);
	  Z=0;
	 // Z=Z+431602080;//Ϊʲô��������431602080�������������ġ�
    pa=pa->next;//������һ��֮������û���Ǹ�˵��431602080��˵���ʼ��Щ�ط���û��ֵ�ġ�
  while(pa!=NULL)
	  //while(u==2)

  {
	  //h=(int)pa->coef;
	  h=ceil(pa->coef);//floatתint
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


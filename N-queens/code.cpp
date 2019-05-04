#include<stdio.h>
#include <GL/glut.h>
#include<time.h>
#include<stdlib.h>

int i,j,queens,w,h,n,k=1,fb=1,choice,moc=0;
int x[10];

void clear_cross(int row_val,int column_val)
{
    if((row_val+column_val) % 2 == 0 )
        glColor3f(0.8,0.8,0.8);
    else
        glColor3f(1,1,1);
}

void draw_cross(int row_val,int column_val,int visible)
{
        float chota = 0.125,medi = .25,maxi = .5;
        if(visible == 0)
            clear_cross(row_val,column_val);
        glBegin(GL_POLYGON);
        glVertex2f(row_val+maxi + chota,column_val+medi);
        glVertex2f(row_val+maxi + medi,column_val+medi + chota);
        glVertex2f(row_val+ medi + chota,column_val+maxi + medi);
        glVertex2f(row_val+medi,column_val+maxi + chota);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(row_val+medi+chota,column_val+medi);
        glVertex2f(row_val+ maxi + medi ,column_val+maxi + chota);
        glVertex2f(row_val+maxi + chota,column_val+maxi + medi);
        glVertex2f(row_val+medi,column_val+medi + chota);
        glEnd();
        glFlush();
        //printf("(%d,%d)",row_val,column_val);
}

int check(int x,int y)
{
    if(x > -1 && x <= queens && y > -1 && y <= queens)
        return 1;
    else
        return 0;
}

void danger_zones(int i,int j,int visible) // starts from 0 -> 3
{
    if(!(check(i,j)))
        return;

    for (int column_val=(queens-1),row_val=i;column_val >=0;column_val--) //coloring the column keep i constant
    {
        if((row_val == i && column_val == j)|| (x[row_val]-1==column_val))
            continue;
        int co=0;
        for(int valk =1;valk<k;valk++)
        {
            if((x[valk]-1==column_val))
            {
                co=1;
                break;
            }
        }
        if(co==1)
            continue;
        draw_cross(row_val,column_val,visible);
    }

    for (int row_val=0,column_val=j;row_val < queens;row_val++) //coloring the row keep j constant
    {
        if((row_val == i && column_val == j) || row_val == i-1)
            continue;
        int co =0;
        for(int valk =1;valk<k;valk++)
        {
            if(row_val == valk-1)
            {
                co=1;
                break;
            }
        }
        if(co==1)
            continue;
        draw_cross(row_val,column_val,visible);
    }

    for (int kc=0,row_val=i,column_val=j;kc <= queens;kc++,row_val++,column_val--)   //coloring both column and row forwards
    {
        if(row_val > (queens-1) && column_val < 0)
        {
            row_val -= queens;
            column_val += queens;
        }
        if(row_val > (queens-1) || column_val > (queens-1) || column_val < 0)
                continue;
        if((row_val == i && column_val == j))
            continue;
        int co = 0;
        for(int valk =1;valk<k;valk++)
        {
            if((x[valk]-1==column_val) || row_val == valk-1)
            {
                co=1;
                break;
            }
        }
        if(co==1)
            continue;

        draw_cross(row_val,column_val,visible);
    }


    for (int kc=0,row_val_rev = i,col_val_rev = j;kc <= queens;kc++,row_val_rev--,col_val_rev--)   //coloring both column and row backwards
    {
        if(row_val_rev < 0 && col_val_rev < 0)
        {
            row_val_rev +=queens;
            col_val_rev += queens;
        }
        if(row_val_rev < 0 || col_val_rev < 0)
                continue;
        if(row_val_rev == i && col_val_rev == j)
            continue;
        int co = 0;
        for(int valk =1;valk<k;valk++)
        {
            if((x[valk]-1==col_val_rev) || row_val_rev == valk-1)
            {
                co=1;
                break;
            }
        }
        if(co==1)
            continue;
        draw_cross(row_val_rev,col_val_rev,visible);
    }

}


void plotpoint(float x_pos,float y_pos)     //plotpoint starts from 1 -> 4      plot the queen
{
    glLineWidth(2);
    glBegin(GL_POLYGON);
        glVertex2f(x_pos-0.3,y_pos-0.2);
        glVertex2f(x_pos-0.1,y_pos-0.7);
        glVertex2f(x_pos-0.35,y_pos-0.4);
        glVertex2f(x_pos-0.35-0.15/2+0.1,y_pos-0.9);
        glVertex2f(x_pos-0.5,y_pos-0.5);
        glVertex2f(x_pos-0.5-0.15/2-0.1,y_pos-0.9);
        glVertex2f(x_pos-0.65,y_pos-0.4);
        glVertex2f(x_pos-0.9,y_pos-0.7);
        glVertex2f(x_pos-0.7,y_pos-0.2);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(x_pos-0.3,y_pos-0.2);
        glVertex2f(x_pos-0.2,y_pos-0.1);
        glVertex2f(x_pos-0.8,y_pos-0.1);
        glVertex2f(x_pos-0.7,y_pos-0.2);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(x_pos-0.2,y_pos-0.1);
        glVertex2f(x_pos-0.8,y_pos-0.1);
        glVertex2f(x_pos-0.9,y_pos-0.05);
        glVertex2f(x_pos-0.1,y_pos-0.05);
    glEnd();
    glFlush();
}

int place(int x[],int k)
{
    for (int i=1;i<=k-1;i++)
    {
        if(x[i]==x[k] || abs(i-k) == abs(x[i]-x[k]))
            return 0;
    }
    return 1;
}

void cvtD2B(int n)
{   int bin[4] = {0,0,0,0};
    int remainder,base=1,sum=0,index=0;

    if(n >4)
        n-=4;
    if(n == 3)
        n=5;
    while(n!=0)
    {
        remainder = n%2;
        n/=2;
        sum += remainder * base;
        base *=10;
    }
    //printf("%d\n",sum);
    while(sum!=0)
    {
        remainder = sum%10;
        //printf("%d\n",remainder);
        bin[index]=remainder;
        index++;
        sum/=10;
    }
    glColor3f(bin[2],bin[1],bin[0]);
}

void draw_zones()
{
    if(k>1 && fb==1)
    {
        cvtD2B(k-1);
        danger_zones(k-2,x[k-1]-1,1);
    }
    if(fb ==0)
    {
        danger_zones(k-1,x[k]-1,0);
        for (int all=1;all<k;all++)
        {
            cvtD2B(all);
            danger_zones(all-1,x[all]-1,1);
        }
    }


}
void disappear(float x_pos,float y_pos) //remove the cross-marks and plot points and positions occupied by placing the queen just a row below
{
    clear_cross(x_pos,y_pos);  //returns the background color auto done!!!
    plotpoint(x_pos,y_pos);
    if (choice ==3)
        return;
    Sleep(300);
}

void appear(float x_pos,float y_pos)
{
    cvtD2B(k);
    plotpoint(x_pos,y_pos);
    if (choice ==3)
        return;
    Sleep(300);
}

int get_posqueen()
{   int yqpos = x[k];
    for(int i=1;i<k;i++)
    {
        if(yqpos == x[i])
            return i;
    }
    return k-1;
}

void nqueens()
{
    int  color=0; //take as such
    x[k] = 0;//place it in this position initial queen->1 row->0
    plotpoint(k,x[k]); //placing the queen at 1,0

    while(k!=0)
    {
        if (fb==1 && choice == 1)
            draw_zones();
        if (choice ==1)
            Sleep(500);
        disappear(k,x[k]);
        if (fb==0 && choice == 1)
            draw_zones();
        if (choice ==1)
            Sleep(500);
        x[k] +=1; //consider placing queen k in the position row=k,column=x[k]
        moc++;
        appear(k,x[k]);

        while((x[k]<=n)&&(!place(x,k)))
        {
            disappear(k,x[k]);
            if (choice == 1)
            {
                color = get_posqueen();
                cvtD2B(color);
                draw_cross(k-1,x[k]-1,1);
            }
            x[k] +=1; //consider placing queen k in the position row=k,column=x[k]
            moc++;
            appear(k,x[k]);
         }
        if(x[k]<=n)
        {
            if(k==n)
            {
                break;
            }
            else
            {
                k++; //consider the next queen
                fb=1;
                disappear(k,x[k]);
                x[k]=0; // place it in this position
                appear(k,x[k]);
            }
        }
        else
        {
            k--;
            fb=0; //consider the previous queen
        }
    }
    printf("TOTAL NUMBER OF MOVES FOR %d QUEENS is %d",queens,moc-queens);
}


void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    for(j = 0;j <queens ;j++ )
    {
        for(i = 0;i < queens;i++ )
        {
            glBegin(GL_POLYGON);
            if((i%2) == 0)
            {
                if((j%2) == 0)
                    glColor3f (0.8, 0.8, 0.8);
                else
                    glColor3f (1, 1, 1);
            }
            else
            {
                if((j%2) == 0)
                    glColor3f (1, 1, 1);
                else
                glColor3f (0.8, 0.8, 0.8);
            }
            glVertex2f (i,j);
            glVertex2f (i+1,j);
            glVertex2f (i+1,j+1);
            glVertex2f (i,j+1);
            glEnd();
            glFlush ();
        }
    }
    nqueens();
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, queens, queens,0);
}

int main(int argc, char** argv)
{
    printf("SOLVING N-QUEENS PUZZLE\n");
    printf("1.PLOT WITH DANGER POINTS\n2.PLOT WITHOUT DANGER POINTS\n3.DIRECT OUTPUT\nENTER YOUR CHOICE: ");
    scanf("%d",&choice);

    if(choice<4 && choice> 0)
    {
        printf("Enter the number of queens(maximum=10) :");
        scanf("%d",&queens);
        if(queens < 4)
        {
            printf("NO OUTPUT EXISTS FOR %d QUEENS",queens);
            exit(1);
        }
        if(queens >10)
        {
            printf("EXCEEDS MAXIMUM LIMIT");
            exit(2);
        }
        n = queens;
        w =h= 75*queens;
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize (w, h);
        glutInitWindowPosition (100, 40);
        glutCreateWindow ("Chess Board");
        init ();
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;

    }
    printf("invalid choice encounterd!!! terminating program... ");
    exit(0);
}

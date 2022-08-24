


int OpenFile(char *name,int mode)
{
    int i=0;
    PINODE temp=NULL;

    if(name==NULL||mode<=0)
    {
        return-1;
    }
    temp=Get_Inode(name);
    if(temp==NULL)
    {
        return-2;
    }
    if(temp->permission<mode)
    {
        return-3;
    }
    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable==NULL)
        {
            break;
        }
        i++;
    }

    UFDTArr[i].ptrfiletable=(PFILETABLE)malloc(sizeof(FILETABLE));
    if(UFDTArr[i].ptrfiletable==NULL)
    {
        return-1;
    }
    UFDTArr[i].ptrfiletable->count=1;
    UFDTArr[i].ptrfiletable->mode=mode;
    if(mode==READ+WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset=0;
        UFDTArr[i].ptrfiletable->writeoffset=0;
    }
    else if (mode==READ)
    {
        UFDTArr[i].ptrfiletable->readoffset=0;
    }
    else if(mode==WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset=0;
    }
    UFDTArr[i].ptrfiletable->ptrinode=temp;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
    
    return i;
}

void CloseFileByName(int fd)
{
    UFDTArr[i].ptrfiletable->readoffset=0;
    UFDTArr[i].ptrfiletable->writeoffset=0;
    
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
    
}
int CloseFileByName(char *name)
{
    int i=0;
    i=GetFDFromName(name);
    if(i==-1)
    {
        return-1;
    }

    UFDTArr[i].ptrfiletable->readoffset=0;
    UFDTArr[i].ptrfiletable->writeoffset=0;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;

    return 0;
    

}

void CloseAllFile()
{
    int i=0;
    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable!=NULL)
        {
            UFDTArr[i].ptrfiletable->readoffset=0;
            UFDTArr[i].ptrfiletable->writeoffset=0;
            (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;

            break;
        }
        i++;
    }
}

int LseekFile(int fd,int size,int from)
{
    if((fd<0)||(from>2))
    {
        return-1;
    }
    if(UFDTArr[fd].ptrfiletable==NULL)
    {
        return -1;
    }
    if(UFDTArr[fd].ptrfiletable->mode==READ)||((UFDTArr[FD].ptrfiletable->mode==READ+WRITE))
    {
        if(from==CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->readoffset)+size)>UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
            {
                return -1;

            }
            if((UFDTArr[fd].ptrfiletable->readoffset)+size<0)
            {
                return-1;
            }
            (UFDTArr[fd].ptrfiletable->readoffset)=((UFDTArr[fd].ptrfiletable->readoffset)+size);


        }
        else if(from==START)
        {
            if(size>(UFDTArr[fd].ptrfiletable->FileActualSize))
            {
                return -1;
            }
            if(size<0)
            {
                return -1;
            }
            (UFDTArr[fd].ptrfiletable->readoffset)=size;
        }
        else if(from==END)
        {
            if(size>(UFDTArr[fd].ptrfiletable->FileActualSize)+size)
            {
                return-1;
            }
            if((UFDTArr[fd].ptrfiletable->readoffset)+size<0)
            {
                return -1;
            }
            (UFDTArr[fd].ptrfiletable->readoffset)=((UFDTArr[fd].ptrfiletable->FileActualSize)+size);


        }

    }
    else if(UFDTArr[fd].ptrfiletable->mode==WRITE)
    {
        if(from==CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->writeoffset)+size)>MAXFILESIZE)
            {
                return -1;
            }
            if((UFDTArr[fd].ptrfiletable->writeoffset)+size<0)
            {
                return -1;
            }
            if(((UFDTArr[fd].ptrfiletable->witeoffset)+size)>(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            {
                return -1;
            }
            (UFDTArr[fd].ptrfiletable->->ptrinode->FileActualSize)=((UFDTArr[fd].ptrfiletable->writeoffset)+size);
            (UFDTArr[fd].ptrfiletable->writeoffset)=((UFDTArr[fd].ptrfiletable->writeoffset)+size);

        }
        else if(from==START)
        {
            if(size>MAXFILESIZE)
            {
                return-1;
            }
            if(size>(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            {
                return -1;
            }
            (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)=size;
            (UFDTArr[fd].ptrfiletable->writeoffset)=size;
        }
        else if(from==END)
        {
            if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)+size>MAXFILESIZE)
            {
                return -1;
            }
            if((UFDTArr[fd].ptrfiletable->writeoffset)+size<0)
            {
                return -1;
            }
            (UFDTArr[fd].ptrfiletable->writeoffset)=((UFDTArr[fd].ptrfiletable->ptrinode->FileAcutalSize)+size);


        }
    }
}
void ls_file()
{
    int i=0;
    PINODE temp=head;

    if(SUPERBLOCKobj.FreeInode==MAXINODE)
    {
        printf("error:there are no files\n");
        return;
    }
    printf("\nfile name\tInode number\tFile size\tLink count\n");
    printf("...................................................\n");
    while(temp!=Null)
    {
        if(temp->FileType!=0)
        {
            printf("%s\t\t%d\t\t%d\t\t%d\n",temp->FileName,temp->InodeNumber,temp->FileActualSize,temp->LinkCount);

        }
        temp=temp->next;
    }
    printf("....................................................\n");

}
int fstat_file(int fd)
{
    PINODE temp=head;
    int i=0;
    if(fd<0)
    {
        return -1;
    }
    if(UFDTArr[fd].ptrfiletable==NULL)
    {
        return -2;
    }
    temp=UFDTArr[fd].ptrfiletable->ptrinode;

    printf("\n.........Statistical Information about file.......\n");
    printf("file name:%s\n,temp->FileName");
    printf("Inode Number %d\n,temp->InodeNumber");
    printf("File Size:%d\n",temp->FileSize);
    printf("Actual File Size:%d\n",temp->FileActualSize);
    printf("Link count:%d\n",temp->LinkCount);
    printf("Reference count:%d\n",temp->ReferenceCount);

    if(temp->permission==1)
    {
        printf("file permission:Read only\n");
    }
    else if(temp->permission==2)
    {
        printf("file permission:write\n");
    }
    else if(temp->permission==3)
    {
        printf("file permission:Read and write\n");
    }
    printf("................................\n\n");

    return 0;
}

int stat_file(char *name)
{
    PINODE temp=head;
    int i=0;
    if(name==NULL)
    {
        return -1;
    }
    while(temp!==NULL)
    {
        if(strcmp(name,temp->FileName)==0)
        {
            break;
        }
        temp=temp->next;

    }
    if(temp==NULL)
    {
        return -2;
    }

    printf("\n.........Statistical Information about file.......\n");
    printf("file name:%s\n,temp->FileName");
    printf("Inode Number %d\n,temp->InodeNumber");
    printf("File Size:%d\n",temp->FileSize);
    printf("Actual File Size:%d\n",temp->FileActualSize);
    printf("Link count:%d\n",temp->LinkCount);
    printf("Reference count:%d\n",temp->ReferenceCount);

    if(temp->permission==1)
    {
        printf("file permission:Read only\n");
    }
    else if(temp->permission==2)
    {
        printf("file permission:write\n");
    }
    else if(temp->permission==3)
    {
        printf("file permission:Read and write\n");
    }
    printf("................................\n\n");

    return 0;
}

int truncate_File(char *name)
{
    int fd=GetFDFromName(name);
    if(fd==-1)
    {
        return -1;
    }
    memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer,0,1024);
    UFDTArr[fd].ptrfiletable->readoffset=0;
    UFDTArr[fd].ptrfiletable->writeoffset=0;
    UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize=0;

    
}

int main()
{
    char *ptr=NULL;
    int ret=0,fd=0,count=0;
    char command[4][80],str[80],arr[1024];

    InitialiseSuperBlock();
    CreateDILB();

    while(1)
    {
        fflush(stdin);
        strcpy(str,"");

        printf("\nMarvellous VFS:>");

        fgets(str,80,stdin);

        count=sscanf(str,"%s %s %s",command[0],command[1],command[2],command[3]);

        if(count==1)
        {
            if(strcmp(command[0],"ls")==0)
            {
                ls_file();
            }
            else if(strcmp(command[0],"closeall")==0)
            {
                CloseAllFile();
                printf("All files closed successufully\n");
                continue;
            }
            else if(strcmp(command[0],"clear")==0)
            {
                system("cls");
                continue;
            }
            else if(strcmp(command[0],"help")==0)
            {
                DisplayHelp();
                continue;
            }
            else if(strcmp(command[0],"exit")==0)
            {
                printf("Terminating the marvellous virtual file system\n ");
                break;;
            }
            else
            {
                printf("\nEROOR:command not found!!!\n");
                continue;
            }

        }
        else if(count==2)
        {
            if(strcmp(command[0],"stat")==0)
            {
                ret=stat_file(command[1]);
                if(ret==-1)
                {
                    printf("ERROR:Incorrect parramter\n");
                }
                if(ret==-2)
                {
                    printf("ERROR:there is no such file\n");

                }
                continue;
            }
            else if(strcmp(command[0],"fstat")==0)
            {
                ret=fstat_file(atoi(command[1]));
                if(ret==-1)
                {
                    printf("ERROR:Incorrect parramter\n");
                }
                if(ret==-2)
                {
                    printf("ERROR:there is no such file\n");

                }
                continue;
            }
            else if(strcmp(command[0],"close")==0)
            {
                ret=CloseFileByName(command[1]);
                if(ret==-1)
                {
                    printf("ERROR:there is no such file\n");
                }
                
                continue;
            }
            else if(strcmp(command[0],"rm")==0)
            {
                ret=rm_File(command[1]);
                if(ret==-1)
                {
                    printf("ERROR:there is no such file\n");
                }
                
                continue;
            }
            else if(strcmp(command[0],"man")==0)
            {
                man(command[1]);
                
            }
            else if(strcmp(command[0],"write")==0)
            {
                fd=GetFromName(command[1]);
                if(ret==-1)
                {
                    printf("ERROR:incorrect parameter\n");
                    continue;
                }
                printf("enter the data:\n");
                scanf("%[^\n]",arr);

                ret=strlen(arr);
                if(ret==0)
                {
                    printf("Error:incorrect parametr\n");
                    continue;
                }
                ret=WriteFile(fd,arr,ret);
                if(ret==-1)
                {
                    printf("error:permission denied\n");
                }
                if(ret==-2)
                {
                    printf("error:there is no sufficient memmory to write\n");
                }
                if(ret==-3)
                {
                    printf("error:it is regular file\n");
                }
                
                
            }
            else if(strcmp(command[0],"truncate")==0)
            {
                ret=truncate_File(command[1]);
                if(ret==-1)
                {
                    printf("error:Incorrect pararmeter\n");
                }
                else
                {
                    printf("\nERROR:command not found!!!\n");
                    continue;
                }
            }
        }
        else if(count==3)
        {
            if(strcmp(command[0],"create")==0)
            {
                ret=Createfile(command[1],atoi(command[2]));
                if(ret>=0)
                {
                    printf("File is succcessfully created with file descriptor:%d\n",ret);

                }
                if(ret==-1)
                {
                    printf("ERROR:incorrect parameter\n");
                }
                if(ret==-2)
                {
                    printf("ERROR:there is no inodes\n");
                }
                if(ret==-3)
                {
                    printf("ERROR:file already exists\n");
                }
                if(ret==-4)
                {
                    printf("ERROR:memory allocation failure\n");
                }
                continue;
            }
            else if(strcmp(command[0],"open")==0)
            {
                ret=Createfile(command[1],atoi(command[2]));
                if(ret>=0)
                {
                    printf("File is succcessfully opened  with file descriptor:%d\n",ret);

                }
                if(ret==-1)
                {
                    printf("ERROR:incorrect parameter\n");
                }
                if(ret==-2)
                {
                    printf("ERROR:file is not present\n");
                }
                if(ret==-3)
                {
                    printf("ERROR:permission denied\n");
                }
                
                continue;
            }
            else if(strcmp(command[0],"read")==0)
            {
                fd=GetFDFromName(command[1]);
                
                if(ret==-1)
                {
                    printf("ERROR:incorrect parameter\n");
                    continue;
                }
                ptr=(char *)malloc(sizeof(atoi(command[2]))+1);

                if(ptr==NULL)
                {
                    printf("ERROR:memory allocaation failure\n");
                    continue;
                }
                ret=ReadFile(fd,ptr,atoi(command[2]));
                if(ret==-1)
                {
                    printf("ERROR:file not existing\n");
                }
                if(ret==-2)
                {
                    printf("ERROR:permission denied\n");
                }
                if(ret==-3)
                {
                    printf("ERROR:reached atend of file\n");
                }
                if(ret==-4)
                {
                    printf("ERROR:it is not regular file\n");
                }
                if(ret>0)
                {
                    write(2,ptr,ret);
                }
                
                continue;
            }
            else
            {
                printf("\nERROR:Command not found!!!\n");
                continue;
            }
        }
        else if(count==4)
        {
            if(strcmp(command[0],"lseek")==0)
            {
                fd=GetDFFromName(command[1]);
                if(fd==-1)
                {
                    printf("Error:incorrect pararmter\n");
                    continue;
                }
                ret=LseekFile(fd,atoi(command[2],atoi(command[3])));
                if(ret==-1)
                {
                    printf("ERROR:Unable to perform lseek\n");
                }

            }
            else
            {
                printf("\nError:Command not found!!\n");
                continue;
            }

        }
        else
        {
            printf("\nError:Command not found!!\n");
            continue;

        }
    }
    return 0;
}





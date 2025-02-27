    #include<sharedmemory.h>


void wthread::memory_init()
{

    QSharedMemory *share=new QSharedMemory("data");
    share->setNativeKey("data");

    share->create(sizeof(rbt_data),QSharedMemory::ReadWrite);
    da=(rbt_data*)share->data();






}
void wthread::send()
{
    memcpy(&da->in,&this->input.in,sizeof(input.in));
    memcpy(&this->input.out,&da->out,sizeof(da->out));

}

#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

class RingBuffer
{
    public:

    /*initialize ring buffer with a prespecified size, set up variables:
     *  m_itemsCurrentlyStored, tail and head (which starts from the end of the array to satisfy the first addition to the buffer)
    */
    RingBuffer(int bufferSize):m_bufferSize(bufferSize),
                                m_underlyingBuffer (new int[bufferSize]),
                                    m_itemsCurrentlyStored(0),//start as if it was full
                                        head(bufferSize-1),
                                        tail(0)
    {
        memset( m_underlyingBuffer.get(), 0, bufferSize * sizeof( int ));
    }

    //push (update both head and tail indices accordingly as well as increment head index to pointer to the next buffer posiion to write to)
    void push(int value)
    {

        // if buffer full, make sure tail gets incremented to point to the next element from
        //what it was pointing to before cause the new element added to the ring buffer will overwrite
        //the oldest in
        if (m_itemsCurrentlyStored==m_bufferSize)
        {
            //increment head pointer
            head = movePointerToNextElement(head);
            //add data to buffer
            m_underlyingBuffer[head] = value;

            tail = movePointerToNextElement(tail);
        }
        else
        {
            //increment the amount of elements stored in the buffer
            m_itemsCurrentlyStored++;

            //increment head pointer
            head = movePointerToNextElement(head);
            //add data to buffer
            m_underlyingBuffer[head] = value;
        }


    }

    //pop
    int pop()
    {
        //buffer not empty
        if (m_bufferSize<=0)
        {
            m_itemsCurrentlyStored--;

            int retElement = m_underlyingBuffer[tail];
            //zero out position , but not nessecarily
            m_underlyingBuffer[tail] = 0;

            //move tail to next index
            tail = movePointerToNextElement(tail);

            return retElement;
        }
    }

    //advance head pointer to the next position on the circular buffer, so as to write data to
    int movePointerToNextElement(int curpos)
    {
        return (curpos + 1) % m_bufferSize;
    }


    private :
            int m_bufferSize;
            int m_itemsCurrentlyStored;
            int head, tail;
            std::unique_ptr<int[]> m_underlyingBuffer;

};


int main(int argc, char *argv[])
{



    const int bufferSize = 5;
    RingBuffer r(bufferSize);
    r.push(1);
    r.push(2);
    r.push(3);
    r.push(4);
    r.push(5);
    r.push(6);

    r.pop();
    r.pop();

    r.push(5);
    r.push(6);
    r.push(7);
    r.push(8);
    r.push(9);

    r.pop();
    r.pop();

    r.push(5);
    r.push(6);
    r.push(8);
    r.push(9);

    r.pop();
    r.pop();
    r.pop();
    r.pop();
    r.pop();
    r.pop();
    r.pop();



    return 0;
}

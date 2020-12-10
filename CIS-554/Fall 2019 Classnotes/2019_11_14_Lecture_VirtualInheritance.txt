//Virtual inheritance
//Diamond problem
class storable //this is the our base class inherited by transmitter and receiver classes
{
        public:
        storable(const char*);
        virtual void read();
        virtual void write(); 
        virtual ~storable();
        private:
        ....
}
 
class transmitter: public storable 
{
        public:
        void write();
        ...
} 
 
class receiver: public storable
{
        public:
        void read();
        ...
}
 
class radio: public transmitter, public receiver
{
        public:
        void read();
        ....
}

//Fix
class transmitter: public virtual storable 
{
        public:
        void read();
        ...
} 
 
class receiver: public virtual storable
{
        public:
        void read();
        ...
} 


order of constructor: storable, transmitter, rceiver
order of destructor: receier, transmitter, storable

//Cross Delegation
//common base class has to be an abstract class

class storable 
{
        public:
        storable(const char*);
        virtual void read()=0; //this becomes pure virtual making storable an abstract
        virtual void write(); //class
        virtual ~storable();
        private:
        ....
}
 
class transmitter: public virtual storable 
{
        public:
        void write()
        {
                read();
                ....
        }
} 
 
class receiver: public virtual storable
{
        public:
        void read();
}
 
class radio: public transmitter, public receiver
{
        public:
        ...
}
 
int main()
{
        radio *rad = new radio();
        receiver *r1 = rad;
        transmitter *r2 =rad;
 
        rad->write();
        r1->write();
        r2->write();
        return 1;
}



#ifndef OBJECT_HPP
#define OBJECT_HPP


class Object{

    protected:
        char* symbol;
    private:

    public:
        Object();
        virtual char getSymbol() const;
};

#endif
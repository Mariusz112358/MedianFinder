#ifndef IMEDIANCOMPUTER_H
#define IMEDIANCOMPUTER_H

class IMedianComputer {
public:
    IMedianComputer();
    virtual ~IMedianComputer();

    virtual void add(int val) = 0;
    virtual double getMedian() = 0;
private:
};

#endif // IMEDIANCOMPUTER_H

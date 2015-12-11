class PairWareContainer
{
private:
    deque<PairWare*> middleWares;
public:

    void add(PairWare& middleWare)
    {
        middleWares.push_back(&middleWare);
    }

    void add(PairWare* middleWare)
    {
        middleWares.push_back(middleWare);
    }

    deque<KeyValuePair> processForInput(deque<KeyValuePair>& pairs, int connectionId)
    {
        for (int i = 0; i < middleWares.size(); i++)
        {
            deque<KeyValuePair> values = middleWares[i]->processInput(pairs, connectionId);
            pairs.clear();
            for (int i = 0; i < values.size(); i++)
            {
                pairs.push_back(values[i]);
            }
        }
        return pairs;
    }

    deque<KeyValuePair> processForOutput(deque<KeyValuePair>& pairs, int connectionId)
    {
        for (int i = middleWares.size() - 1; i >= 0; i--)
        {
            deque<KeyValuePair> values = middleWares[i]->processOutput(pairs, connectionId);
            pairs.clear();
            for (int i = 0; i < values.size(); i++)
            {
                pairs.push_back(values[i]);
            }
        }
        return pairs;
    }
};

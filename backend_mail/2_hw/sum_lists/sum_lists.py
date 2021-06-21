class MyList(list):
    def __add__(self, other):
        ans = MyList()

        n1 = len(self)
        n2 = len(other)
        n = max(n1, n2)

        for i in range(n):
            if i < n1 and i < n2:
                ans.append(self[i] + other[i])
            elif i < n1:
                ans.append(self[i])
            elif i < n2:
                ans.append(other[i])
        return ans

    def __radd__(self, other):
        ans = MyList()

        n1 = len(self)
        n2 = len(other)
        n = max(n1, n2)

        for i in range(n):
            if i < n1 and i < n2:
                ans.append(self[i] + other[i])
            elif i < n1:
                ans.append(self[i])
            elif i < n2:
                ans.append(other[i])
        return ans

    def __sub__(self, other):
        ans = MyList()
        n1 = len(self)
        n2 = len(other)
        n = max(n1, n2)
        for i in range(n):
            if i < n1 and i < n2:
                ans.append(self[i] - other[i])
            elif i < n1:
                ans.append(self[i])
            elif i < n2:
                ans.append(-other[i])
        return ans

    def __rsub__(self, other):
        ans = MyList()
        n1 = len(self)
        n2 = len(other)
        n = max(n1, n2)
        for i in range(n):
            if i < n1 and i < n2:
                ans.append(-(self[i] - other[i]))
            elif i < n1:
                ans.append(-(self[i]))
            elif i < n2:
                ans.append(-(-other[i]))
        return ans

    def __cmp__(self, other):
        sum1 = 0
        # sum(self)
        for x in self:
            sum1 += x

        sum2 = 0
        for x in other:
            sum2 += x

        return sum1.__cmp__(sum2)

    def __rcmp__(self, other):
        sum1 = 0
        for x in self:
            sum1 += x

        sum2 = 0
        for x in other:
            sum2 += x

        return sum1.__cmp__(sum2)

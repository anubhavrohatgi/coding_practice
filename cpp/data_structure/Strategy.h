class Strategy {
	protected:
		int m_size;

	public:
		Strategy(int size) : m_size(size) {}
		virtual int handleGet(int key) = 0;
		virtual void handlePut(int key, int value) = 0;
		virtual void printCache() = 0;
};

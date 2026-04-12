class Texture {
public:
    Texture();
    Texture(const char* path);
    void bind(unsigned int slot = 0);

private:
    unsigned int ID;

    void createDefault();
};

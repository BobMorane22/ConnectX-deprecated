// Creates a copy for each novel...
for(auto novel : library)
{
    novel.format();
}

// No copy.
for(auto& novel : library)
{
    novel.format();
}

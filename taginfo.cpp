#include "taginfo_impl.hpp"
#include <cassert>

taginfo::taginfo() 
    : name(), type(), flags(0) {
}

taginfo::taginfo(const taginfo &other)
    : name(other.name), type(other.type),
      flags(other.flags) {
}

export_list::export_list()
    : num_tables(0), exportList() {
}

void export_list::add(enum OsmType id, const taginfo &info) {
    std::vector<taginfo> &infos = get(id);
    infos.push_back(info);
}

std::vector<taginfo> &export_list::get(enum OsmType id) {
    if (id >= num_tables) {
        exportList.resize(id+1);
        num_tables = id + 1;
    }
    return exportList[id];
}

const std::vector<taginfo> &export_list::get(enum OsmType id) const {
    // this fakes as if we have infinite taginfo vectors, but
    // means we don't actually have anything allocated unless
    // the info object has been assigned.
    static const std::vector<taginfo> empty;

    if (id < num_tables) {
        return exportList[id];
    } else {
        return empty;
    }
}

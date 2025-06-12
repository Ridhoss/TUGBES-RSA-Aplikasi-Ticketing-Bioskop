#include "header/ADTTree.h"
#include "header/ADTKota.h"
#include "header/ADTBioskop.h"
#include "header/ADTTeater.h" 

static int currentId = 1;

// Deskripsi : Melakukan Cek Apakah Tree Kosong
// IS : menerima address root dari tree
// FS : mengembalikan true jika tree kosong, false jika tidak
boolean IsTreeEmpty(address root) {
    return (root == NULL || root->fs == NULL);
}

// Deskripsi : Alokasi Memori untuk Node Baru
// IS : menerima infotype X yang akan disimpan dalam node
// FS : mengembalikan address dari node yang dialokasikan, atau NULL jika alokasi gagal
address Alokasi(infotype X, NodeType tipe) {
    address P = (address) malloc(sizeof(Node));
    if (P != NULL) {
        P->id = currentId++;
        P->info = X;
        P->pr = NULL;
        P->fs = NULL;
        P->nb = NULL;
        P->type = tipe;
    }
    return P;
}

// Deskripsi : Dealokasi Memori untuk Node
// IS : menerima address P yang berisi node yang akan di-dealokasi
// FS : menghapus alokasi memori dari node P
void Dealokasi(address P) {
    free(P->info);
    free(P);
}

// Deskripsi : Membuat Tree Baru dengan Node Root
// IS : menerima infotype rootInfo yang akan menjadi informasi pada node root
// FS : mengembalikan address dari node root yang baru dibuat, atau NULL jika alokasi gagal
address CreateTree(infotype rootInfo, NodeType tipe) {
    return Alokasi(rootInfo, tipe);
}

// Deskripsi : Menambahkan Node Sebagai Anak dari Node Parent
// IS : menerima address parent dan infotype childInfo yang akan disimpan pada node anak
// FS : menambahkan node anak ke dalam tree sebagai anak dari parent
void AddChild(address parent, infotype childInfo, NodeType tipe) {
    if (parent == NULL) return;

    address child = Alokasi(childInfo, tipe);
    if (child == NULL) return;

    child->pr = parent;

    if (parent->fs == NULL) {
        parent->fs = child;
    } else {
        address sibling = parent->fs;
        while (sibling->nb != NULL) {
            sibling = sibling->nb;
        }
        sibling->nb = child;
    }
}

// Deskripsi : Prosedur untuk Mencari Node dalam Tree
// IS : menerima address root, infotype searchinfo yang akan dicari, dan fungsi pembanding cmp
// FS : mengembalikan address dari node yang sesuai dengan searchinfo, atau NULL jika tidak ditemukan
address Search(address root, infotype searchinfo, CompareFunc cmp, NodeType tipeNode) {
    if (root == NULL) return NULL;

    if (root->type == tipeNode && cmp(root->info, searchinfo) == 0) {
        return root;
    }

    address found = Search(root->fs, searchinfo, cmp, tipeNode);
    if (found != NULL) {
        return found;
    }

    return Search(root->nb, searchinfo, cmp, tipeNode);
}

// Deskripsi : Prosedur untuk Mengubah Informasi pada Node
// IS : menerima address node yang akan diubah dan infotype newInfo yang akan disimpan pada node
// FS : mengubah informasi pada node dengan newInfo
void UbahNode(address node, infotype newInfo) {
    if (node != NULL) {
        node->info = newInfo;
    }
}

// Deskripsi : Prosedur untuk Menghapus Semua Node dalam Tree
// IS : menerima address node yang akan dihapus
// FS : menghapus semua node dalam tree, termasuk node itu sendiri
void DeleteAll(address node) {
    if (node == NULL) return;

    address nextSibling = node->nb;
    DeleteAll(node->fs);
    Dealokasi(node);
    DeleteAll(nextSibling);
}

// Deskripsi : Prosedur untuk Menghapus Semua Node dalam Tree, kecuali Root
// IS : menerima address node yang akan dihapus, tetapi tetap menyimpan root
// FS : menghapus semua node dalam tree, kecuali root node itu sendiri
void DeleteAllKeepRoot(address node) {
    if (node == NULL || node->fs == NULL) return;

    address child = node->fs;
    node->fs = NULL;

    while (child != NULL) {
        address next = child->nb;
        child->nb = NULL;
        child->pr = NULL;
        DeleteAll(child);
        child = next;
    }
}

// Deskripsi : Prosedur untuk Menghapus Node Tertentu dari Tree
// IS : menerima address root dari tree dan address delNode yang akan dihapus
// FS : menghapus node delNode dari tree, termasuk semua anak dan saudara dari delNode
void DeleteNode(address *root, address delNode) {
    if (delNode == NULL || root == NULL || *root == NULL) return;

    if (*root == delNode) {
        DeleteAll(*root);
        *root = NULL;
        return;
    }

    address parent = delNode->pr;
    if (parent == NULL) return;

    if (parent->fs == delNode) {
        parent->fs = delNode->nb;
        if (parent->fs != NULL) {
            parent->fs->pr = parent;
        }
    } else {
        address sibling = parent->fs;
        while (sibling != NULL && sibling->nb != delNode) {
            sibling = sibling->nb;
        }
        if (sibling != NULL) {
            sibling->nb = delNode->nb;
            if (sibling->nb != NULL) {
                sibling->nb->pr = parent;
            }
        }
    }

    delNode->pr = NULL;
    delNode->nb = NULL;

    DeleteAll(delNode);
}

// Deskripsi : Prosedur untuk Mencetak Tree
// IS : menerima address node yang akan dicetak dan level untuk indentasi
// FS : mencetak informasi dari node dan semua anaknya dengan indentasi sesuai level
void PrintTree(address node, int level) {
    if (node == NULL) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("- %s\n", node->info);
    PrintTree(node->fs, level + 1);
    PrintTree(node->nb, level);
}

// Deskripsi : Prosedur untuk Mencetak Hanya Anak dari Node Tertentu
// IS : menerima address node yang akan dicetak dan level untuk indentasi
// FS : mencetak informasi dari semua anak node tersebut dengan indentasi sesuai level
void PrintChildrenOnly(address node, int level) {
    if (node == NULL || node->fs == NULL) return;

    address child = node->fs;
    while (child != NULL) {
        for (int i = 0; i < level; i++) printf("  ");
        if (child->type == KOTA) {
            KotaInfo* info = (KotaInfo*) child->info;
            printf("- Id: %d Kota: %s\n", info->id, info->nama);
        } else if (child->type == BIOSKOP) {
            BioskopInfo* info = (BioskopInfo*) child->info;
            printf("- Bioskop: %s\n", info->nama);
        } else if (child->type == TEATER) {
            TeaterInfo* info = (TeaterInfo*) child->info;
            printf("- Teater: %s || Jumlah Kursi: %d || Harga: %d\n", info->nama, info->jumlahKursi, info->harga);
        }
        // PrintTree(child->fs, level + 1);
        child = child->nb;
    }
}

// Deskripsi : Prosedur untuk Membaca Input String
// IS : menerima buffer untuk menyimpan input string
// FS : membaca input string dari stdin hingga newline
void InputString(char* buffer) {
    scanf(" %[^\n]", buffer);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());//theres also mt19937_64 for 64 bit random integers

struct item {
    bool rev;
    ll key, prior, cnt; //priorities should be random integers !!!
    ll sum;
    ll mn;
    item * l, * r;
    item() { }
    item (ll key, ll prior) : key(key), prior(prior), l(NULL), r(NULL), sum(key), mn(key), rev(false) { }
};
typedef item * pitem;


int cnt (pitem t) {return t ? t->cnt : 0;}
ll sum(pitem t){return t ? t->sum : 0;}
ll min(pitem t){return t ? t->mn : oo;}

void upd_cnt (pitem t) {
    if (t)t->cnt = 1 + cnt(t->l) + cnt (t->r);
    if (t)t->sum = t->key + sum(t->l) + sum(t->r);
    if (t)t->mn = min({t->key, min(t->l), min(t->r)});
}

void split (pitem t, ll key, pitem & l, pitem & r) { //normal split if using explict keys

    if (!t)l = r = NULL;
    else if (key < t->key)split (t->l, key, l, t->l),  r = t;
    else split (t->r, key, t->r, r),  l = t;

    upd_cnt(t);
}


void push (pitem& it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void split (pitem t, pitem & l, pitem & r, int key, int add) { //split for implict keys
    if (!t)return void( l = r = 0 );
    push (t); //<<this is for lazy propagation
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)split (t->l, l, t->l, key, add),  r = t;
    else split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)t = l ? l : r;
    else if (l->prior > r->prior)merge (l->r, l->r, r),  t = l;
    else merge (r->l, l, r->l),  t = r;

    upd_cnt(t);
}

void insertImplict(pitem & t, pitem it, int pos)
{
    pitem le,ri,tmp;
    split(t,le,ri,pos,0);
    merge(tmp,le,it);
    merge(t,tmp,ri);
    upd_cnt(t);
}

void insert (pitem & t, pitem it) {
    if (!t)t = it;
    else if (it->prior > t->prior)split (t, it->key, it->l, it->r),  t = it;
    else insert (it->key < t->key ? t->l : t->r, it);

    upd_cnt(t);
}

void erase (pitem & t, ll key) {
    if (t->key == key)merge (t, t->l, t->r);
    else erase (key < t->key ? t->l : t->r, key);
}

bool Find(pitem t, int x)
{
    if(!t)return 0;
    if(t->key == x)return 1;
    if(x < t->key)return Find(t->l,x);
    return Find(t->r,x);
}

ll getSumImplict(pitem& t, int l, int r)
{
    pitem le,ri,le2,ri2;
    split(t,le,ri,l,0);
    split(ri,le2,ri2,r-l+1,0);
    ll res = sum(le2);
    merge(ri,le2,ri2);
    merge(t,le,ri);
    return res;
}

void reverse (pitem& t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l,0);
    split (t2, t2, t3, r-l+1,0);
    t2->rev ^= true;
    push(t2);
    merge (t, t1, t2);
    merge (t, t, t3);
    upd_cnt(t);
}

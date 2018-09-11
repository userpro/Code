void add(int u,int v,int w)  
{  
    edge[cnt].w = w;  
    edge[cnt].to = v;  
    edge[cnt].next = head[u];  
    head[u] = cnt++;  
} 
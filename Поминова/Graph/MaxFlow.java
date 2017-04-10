package Graph;

import java.util.*;
import java.lang.*;
import java.util.LinkedList;

public class MaxFlow {

   //return true if there is path from s to t and store the path in parent[]
    boolean bfs(int rGraph[][],int V, int s, int t, int parent[])
    {
        boolean visited[] = new boolean[V];
        for(int i=0; i<V; ++i)
            visited[i]=false;

        LinkedList<Integer> queue = new LinkedList();
        queue.add(s);
        visited[s] = true;
        parent[s] = -1;

        while (queue.size()!=0)
        {
            int u = queue.poll();

            for (int i = 0; i < V; i++)
            {
                if (visited[i]==false && rGraph[u][i] > 0)
                {
                    queue.add(i);
                    parent[i] = u;
                    visited[i] = true;
                }
            }
        }

        //if we have path from s to t return true
        return (visited[t] == true);
    }

    // Returns tne maximum flow from s to t
    int fordFulkerson(int graph[][],int V, int s, int t)
    {
        int u, v;
        int rGraph[][] = new int[V][V];

        for (u = 0; u < V; u++)
            for (v = 0; v < V; v++)
                rGraph[u][v] = graph[u][v];

        // This array is filled by BFS and store path
        int parent[] = new int[V];
        int maxFlow = 0;

        // while there is path from s to t
        while (bfs(rGraph,V, s, t, parent))
        {
            // Find minimum capacity of the edges along the path filled by bfs
            int pathFlow = Integer.MAX_VALUE;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                pathFlow = Math.min(pathFlow, rGraph[u][v]);
            }

            // update residual capacities of the edges and
            // reverse edges along the path
            for (v=t; v != s; v=parent[v])
            {
                u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
            }

            // Add path flow to overall flow
            maxFlow += pathFlow;
        }

        return maxFlow;
    }

    public static void main (String[] args) throws java.lang.Exception
    {
        Scanner reader = new Scanner(System.in);
        int n,m;
        int a,b,c;
        int graph[][] = new int[30][30];
        MaxFlow maxFl = new MaxFlow();

        System.out.println("Enter amount of vertex and edges: ");
        n = reader.nextInt();
        m = reader.nextInt();

        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                graph[i][j] = 0;

        for (int i=0;i<m;i++) {
            System.out.println("Enter number of first vertex, number of second vertex and capacity of edge : ");
            a = reader.nextInt();
            b = reader.nextInt();
            c = reader.nextInt();
            graph[a-1][b-1] = c;
        }

        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
                System.out.print(graph[i][j] + " ");
            System.out.println("");
        }

        System.out.println("The maximum possible flow is " +
                maxFl.fordFulkerson(graph, n, 0, n-1));

    }
}


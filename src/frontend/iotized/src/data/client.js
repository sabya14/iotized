export const jsonFetcher = (resource, init) => fetch(
    resource, init
).then(res => res.json());

export const swrConfigs = {
    refreshInterval: 500,
    dedupingInterval: 500,
    fetcher: jsonFetcher
};

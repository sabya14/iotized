import React from "react";

export const createEnum = (...keys) => Object.freeze(
    Object.fromEntries(keys.map(t => [t, Symbol(t)]))
);



export const dateTimeFormatter = (t) => new Date(parseInt(t)).toDateString();

export const asImage = (urlBuilder, props) => (t) => (<img src={urlBuilder(t)} {...props}/>);


export const toDataset = (items, columnMappings = null) => ({
        columns: (columnMappings ?? Object.keys(items[0]).map(k => [k, k]))
            .map(([k, v]) => ({
                field: k,
                headerName: (v?.headerName || v?.toString() || k),
                ...((typeof v === 'string') ? {} : v)
            })),
        rows: items.map((t, i) => Object.fromEntries(
            Object.entries({id: i, ...t})
                .map(([k, v]) => [k, ((typeof v === 'object') ? JSON.stringify(v) : v)])
        )),
    })
;
